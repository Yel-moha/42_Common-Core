#!/usr/bin/env python3
import re
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parent
TEST_FILE = ROOT / "test_minishell_10_02_2025.txt"
TMP_DIR = ROOT / ".tmp_test_compare"
TMP_DIR.mkdir(exist_ok=True)

INSTR = TMP_DIR / "case_instrumented.sh"
MINI_RAW = TMP_DIR / "case_minishell.raw"
BASH_RAW = TMP_DIR / "case_bash.raw"
REPORT = TMP_DIR / "case_report.txt"
REPORT_MD = TMP_DIR / "case_report.md"

MARKER_RE = re.compile(r"__CASE_END__(\d{4})__(\d+)")
ANSI_CSI_RE = re.compile(r"\x1b\[[0-?]*[ -/]*[@-~]")
ANSI_OSC_RE = re.compile(r"\x1b\][^\x07]*(?:\x07|\x1b\\)")


def read_cases(path: Path):
    lines = path.read_text(encoding="utf-8", errors="replace").splitlines()
    cases = []
    i = 0
    while i < len(lines):
        raw = lines[i]
        line = raw.strip()
        lineno = i + 1
        if not line or line.startswith("#") or line.startswith("["):
            i += 1
            continue

        block = [raw]

        # Best-effort heredoc block grouping: only if all delimiters are found.
        delims = re.findall(r"<<\s*([A-Za-z_][A-Za-z0-9_]*)", raw)
        if delims:
            j = i + 1
            ok = True
            for delim in delims:
                found = False
                scan_limit = min(len(lines), j + 80)
                while j < scan_limit:
                    block.append(lines[j])
                    if lines[j].strip() == delim:
                        found = True
                        j += 1
                        break
                    j += 1
                if not found:
                    ok = False
                    break
            if ok:
                i = j
            else:
                block = [raw]
                i += 1
        else:
            i += 1

        cases.append({"id": len(cases) + 1, "line": lineno, "text": "\n".join(block)})
    return cases


def build_instrumented(cases):
    out = []
    for case in cases:
        out.append(case["text"])
        out.append(f"printf '__CASE_END__{case['id']:04d}__%d\\n' $?")
    INSTR.write_text("\n".join(out) + "\n", encoding="utf-8")


def run_capture(cmd, outfile: Path):
    p = subprocess.run(cmd, cwd=ROOT, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    outfile.write_bytes(p.stdout)


def clean_text(text: str):
    text = text.replace("\r", "")
    text = ANSI_OSC_RE.sub("", text)
    text = ANSI_CSI_RE.sub("", text)
    text = text.replace("minishell$ ", "")
    return text


def parse_segments(raw_text: str):
    text = clean_text(raw_text)
    segments = {}
    prev = 0
    for m in MARKER_RE.finditer(text):
        cid = int(m.group(1))
        status = int(m.group(2))
        seg = text[prev:m.start()]
        prev = m.end()

        cleaned_lines = []
        for ln in seg.splitlines():
            s = ln.strip()
            if not s:
                continue
            if "printf '__CASE_END__" in s:
                continue
            if s == "exit":
                continue
            cleaned_lines.append(ln.rstrip())

        segments[cid] = {"status": status, "output": "\n".join(cleaned_lines).strip()}
    return segments


def strip_echoed_input(output: str, case_text: str):
    case_lines = [ln.strip() for ln in case_text.splitlines() if ln.strip()]
    cleaned = []
    for ln in output.splitlines():
        s = ln.strip()
        if not s:
            continue
        if "__CASE_END__" in s:
            continue
        if "printf '__CASE_END__" in s:
            continue

        matched = False
        for cmd in case_lines:
            if s == cmd:
                matched = True
                break
            if s != cmd and s.endswith(cmd):
                matched = True
                break
        if matched:
            continue

        if re.match(r"^[^$]{1,200}\$\s*$", s):
            continue

        cleaned.append(ln.rstrip())
    return "\n".join(cleaned).strip()


def normalize_for_compare(s: str):
    s = s.replace("\t", " ")
    s = re.sub(r" +", " ", s)
    s = re.sub(r"bash: riga \d+: ", "", s)
    s = re.sub(r"^bash: line \d+: ", "", s, flags=re.MULTILINE)
    s = s.strip()
    return s


def main():
    cases = read_cases(TEST_FILE)
    build_instrumented(cases)

    run_capture("./minishell < .tmp_test_compare/case_instrumented.sh", MINI_RAW)
    run_capture("bash -i < .tmp_test_compare/case_instrumented.sh", BASH_RAW)

    mini_text = MINI_RAW.read_text(encoding="utf-8", errors="replace")
    bash_text = BASH_RAW.read_text(encoding="utf-8", errors="replace")

    mini = parse_segments(mini_text)
    bash = parse_segments(bash_text)

    rows = []
    exact_pass = 0
    soft_pass = 0
    fail = 0

    for case in cases:
        cid = case["id"]
        b = bash.get(cid, {"status": None, "output": "<missing>"})
        m = mini.get(cid, {"status": None, "output": "<missing>"})

        b_out = strip_echoed_input(b["output"], case["text"])
        m_out = strip_echoed_input(m["output"], case["text"])
        b_cmp = normalize_for_compare(b_out)
        m_cmp = normalize_for_compare(m_out)

        if b["status"] == m["status"] and b_out == m_out:
            verdict = "PASS"
            exact_pass += 1
        elif b["status"] == m["status"] and b_cmp == m_cmp:
            verdict = "PASS~"
            soft_pass += 1
        else:
            verdict = "FAIL"
            fail += 1

        rows.append(
            {
                "id": cid,
                "line": case["line"],
                "verdict": verdict,
                "bash_status": b["status"],
                "mini_status": m["status"],
                "cmd": case["text"].splitlines()[0][:90],
                "bash_out": b_out,
                "mini_out": m_out,
            }
        )

    with REPORT.open("w", encoding="utf-8") as f:
        f.write(f"Total cases: {len(rows)}\n")
        f.write(f"PASS exact : {exact_pass}\n")
        f.write(f"PASS soft  : {soft_pass}\n")
        f.write(f"FAIL       : {fail}\n\n")
        f.write("ID  Line  Verdict  B:$?  M:$?  Command\n")
        f.write("-" * 90 + "\n")
        for r in rows:
            f.write(
                f"{r['id']:03d} {r['line']:5d} {r['verdict']:7s} "
                f"{str(r['bash_status']):>4s}  {str(r['mini_status']):>4s}  {r['cmd']}\n"
            )

        f.write("\nDetailed FAIL blocks\n")
        f.write("=" * 90 + "\n")
        for r in rows:
            if r["verdict"] != "FAIL":
                continue
            f.write(f"\n[Case {r['id']:03d} line {r['line']}] {r['cmd']}\n")
            f.write(f"bash $?={r['bash_status']}\n{r['bash_out']}\n")
            f.write(f"minishell $?={r['mini_status']}\n{r['mini_out']}\n")
            f.write("-" * 90 + "\n")

    with REPORT_MD.open("w", encoding="utf-8") as f:
        f.write("# Case-by-case bash vs minishell\n\n")
        f.write(f"- Total: **{len(rows)}**\n")
        f.write(f"- PASS exact: **{exact_pass}**\n")
        f.write(f"- PASS soft: **{soft_pass}**\n")
        f.write(f"- FAIL: **{fail}**\n\n")
        f.write("## Failing cases\n\n")
        for r in rows:
            if r["verdict"] != "FAIL":
                continue
            f.write(f"- Case {r['id']:03d} (line {r['line']}): `{r['cmd']}` | bash $?={r['bash_status']} vs mini $?={r['mini_status']}\n")

    print(f"Wrote: {REPORT}")
    print(f"Wrote: {REPORT_MD}")


if __name__ == "__main__":
    main()
