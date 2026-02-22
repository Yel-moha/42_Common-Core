touch w_block r_block
printf '__CASE_END__0001__%d\n' $?
chmod -w w_block
printf '__CASE_END__0002__%d\n' $?
chmod -r r_block
printf '__CASE_END__0003__%d\n' $?
env
printf '__CASE_END__0004__%d\n' $?
env > w_block
printf '__CASE_END__0005__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0006__%d\n' $?
env < r_block
printf '__CASE_END__0007__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0008__%d\n' $?
export var1 var2= var3="" var4="ciao"
printf '__CASE_END__0009__%d\n' $?
export 123asd="ciao" ?=123 var5?="gotcha" var____2!=7
printf '__CASE_END__0010__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0011__%d\n' $?
export
printf '__CASE_END__0012__%d\n' $?
export > w_block
printf '__CASE_END__0013__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0014__%d\n' $?
export < r_block
printf '__CASE_END__0015__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0016__%d\n' $?
echo     0var4 ?
printf '__CASE_END__0017__%d\n' $?
echo concatenated: 
printf '__CASE_END__0018__%d\n' $?
echo just            one              space here!      !   -n      !       ! 
printf '__CASE_END__0019__%d\n' $?
echo -n -nnnnnnnnnnnnnnnnnnnnnnn -nnmn ciao
printf '__CASE_END__0020__%d\n' $?
echo -n -nnnnn n - nnn ciao
printf '__CASE_END__0021__%d\n' $?
echo 'hello there' > w_block
printf '__CASE_END__0022__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0023__%d\n' $?
echo 'hello there' < r_block
printf '__CASE_END__0024__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0025__%d\n' $?
unset
printf '__CASE_END__0026__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0027__%d\n' $?
unset var1 var2 var3 var4 var5
printf '__CASE_END__0028__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0029__%d\n' $?
unset 123asd="ciao"
printf '__CASE_END__0030__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0031__%d\n' $?
touch not_a_dir
printf '__CASE_END__0032__%d\n' $?
mkdir aaa
printf '__CASE_END__0033__%d\n' $?
mkdir aaa/no_perms_dir
printf '__CASE_END__0034__%d\n' $?
mkdir aaa/no_perms_dir/ccc
printf '__CASE_END__0035__%d\n' $?
chmod 000 aaa/no_perms_dir
printf '__CASE_END__0036__%d\n' $?
export home=/home/yel-moha
printf '__CASE_END__0037__%d\n' $?
unset HOME
printf '__CASE_END__0038__%d\n' $?
cd
printf '__CASE_END__0039__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0040__%d\n' $?
cd do_not_exist
printf '__CASE_END__0041__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0042__%d\n' $?
cd not_a_dir
printf '__CASE_END__0043__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0044__%d\n' $?
cd aaa/no_perms_dir/ccc
printf '__CASE_END__0045__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0046__%d\n' $?
chmod 777 aaa/no_perms_dir
printf '__CASE_END__0047__%d\n' $?
rm -rf not_a_dir aaa
printf '__CASE_END__0048__%d\n' $?
export HOME=
printf '__CASE_END__0049__%d\n' $?
pwd
printf '__CASE_END__0050__%d\n' $?
pwd
printf '__CASE_END__0051__%d\n' $?
env | grep PWD
printf '__CASE_END__0052__%d\n' $?
cd ..
printf '__CASE_END__0053__%d\n' $?
env | grep PWD
printf '__CASE_END__0054__%d\n' $?
unset PWD
printf '__CASE_END__0055__%d\n' $?
pwd
printf '__CASE_END__0056__%d\n' $?
cd /home/yel-moha/github/42_Common-Core
printf '__CASE_END__0057__%d\n' $?
env | grep PWD
printf '__CASE_END__0058__%d\n' $?
cd ..
printf '__CASE_END__0059__%d\n' $?
export PWD
printf '__CASE_END__0060__%d\n' $?
exit 1 | exit 2 | exit 3
printf '__CASE_END__0061__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0062__%d\n' $?
exit 10 | exit -10
printf '__CASE_END__0063__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0064__%d\n' $?
error 127
printf '__CASE_END__0065__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0066__%d\n' $?
echo ciao > 
printf '__CASE_END__0067__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0068__%d\n' $?
rm -f out
printf '__CASE_END__0069__%d\n' $?
echo "BIG BOY TEXT" | > out
printf '__CASE_END__0070__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0071__%d\n' $?
cat out 
printf '__CASE_END__0072__%d\n' $?
rm out
printf '__CASE_END__0073__%d\n' $?
rm -f out
printf '__CASE_END__0074__%d\n' $?
ls > out | <out cat
printf '__CASE_END__0075__%d\n' $?
echo sometext > out
printf '__CASE_END__0076__%d\n' $?
ls > out | <out cat
printf '__CASE_END__0077__%d\n' $?
cat out 
printf '__CASE_END__0078__%d\n' $?
rm out
printf '__CASE_END__0079__%d\n' $?
touch w_block r_block
printf '__CASE_END__0080__%d\n' $?
chmod -w w_block
printf '__CASE_END__0081__%d\n' $?
chmod -r r_block
printf '__CASE_END__0082__%d\n' $?
< r_block cat
printf '__CASE_END__0083__%d\n' $?
echo Exit Code: 0 
printf '__CASE_END__0084__%d\n' $?
> w_block echo ciao 
printf '__CASE_END__0085__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0086__%d\n' $?
< r_block greppp
printf '__CASE_END__0087__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0088__%d\n' $?
> w_block greppp
printf '__CASE_END__0089__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0090__%d\n' $?
echo some_text >file1>file2>fil3>w_block>file4
printf '__CASE_END__0091__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0092__%d\n' $?
ls | grep file
printf '__CASE_END__0093__%d\n' $?
rm -f file1 file2 file3 file4
printf '__CASE_END__0094__%d\n' $?
ls > w_block | grep a | grep b | cat > w_block
printf '__CASE_END__0095__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0096__%d\n' $?
echo ciao > 
printf '__CASE_END__0097__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0098__%d\n' $?
rm -f w_block r_block
printf '__CASE_END__0099__%d\n' $?
export ciao=XXXX
printf '__CASE_END__0100__%d\n' $?
echo ciao$""805409''
printf '__CASE_END__0101__%d\n' $?
echo ci$""$''
printf '__CASE_END__0102__%d\n' $?
unset ciao
printf '__CASE_END__0103__%d\n' $?
export a='Paperon"de"Paperoni'
printf '__CASE_END__0104__%d\n' $?
echo '"ciao doveri ieri sera ?" - "non sono fatti tuoi"'
printf '__CASE_END__0105__%d\n' $?
echo Exit Code: 0 
printf '__CASE_END__0106__%d\n' $?
echo "ciao dov'eri ieri sera ?" - "non sono fatti tuoi"
printf '__CASE_END__0107__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0108__%d\n' $?
unset a
printf '__CASE_END__0109__%d\n' $?
e'ch'"o " ciao
printf '__CASE_END__0110__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0111__%d\n' $?
exit 1 | exit 2 | exit 3
printf '__CASE_END__0112__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0113__%d\n' $?
ls -l | grep .c
printf '__CASE_END__0114__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0115__%d\n' $?
ls | grepp a | cat
printf '__CASE_END__0116__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0117__%d\n' $?
echo pippo | grep
printf '__CASE_END__0118__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0119__%d\n' $?
echo "ciao | ls" | grep '' | w"c" -l >out
printf '__CASE_END__0120__%d\n' $?
echo Exit code: 0
printf '__CASE_END__0121__%d\n' $?
cat out 
printf '__CASE_END__0122__%d\n' $?
rm out
printf '__CASE_END__0123__%d\n' $?
ls | << prut cat | grep la > pippo
lalalalalaalla
lolololololol
prut
printf '__CASE_END__0124__%d\n' $?
cat pippo
printf '__CASE_END__0125__%d\n' $?
rm pippo
printf '__CASE_END__0126__%d\n' $?
<< X cat | grep a
ppapapa
popoop
X
printf '__CASE_END__0127__%d\n' $?
<< X | cat
ppapapa
popoop
X
printf '__CASE_END__0128__%d\n' $?
| | |
printf '__CASE_END__0129__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0130__%d\n' $?
>><
printf '__CASE_END__0131__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0132__%d\n' $?
<<>
printf '__CASE_END__0133__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0134__%d\n' $?
>><<
printf '__CASE_END__0135__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0136__%d\n' $?
<<>>
printf '__CASE_END__0137__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0138__%d\n' $?
<|>
printf '__CASE_END__0139__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0140__%d\n' $?
| echo
printf '__CASE_END__0141__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0142__%d\n' $?
<< a << b | | << c cat >out
printf '__CASE_END__0143__%d\n' $?
a
printf '__CASE_END__0144__%d\n' $?
b
printf '__CASE_END__0145__%d\n' $?
echo Exit Code: 0
printf '__CASE_END__0146__%d\n' $?
echo DONE
printf '__CASE_END__0147__%d\n' $?
