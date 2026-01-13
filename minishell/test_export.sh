#!/bin/bash
(echo "export a"; echo "export"; sleep 0.1) | ./minishell | grep "declare -x a"
