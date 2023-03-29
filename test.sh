#!/bin/bash

# テストするコマンドを配列に追加
commands=(
    "ls"
    "echo 'hello world'"
    "echo -nn hoge"
    "echo -n -n hoge"
    "pwd"
    "echo hoge | echo \"huga\""
    "cat main.c | grep \"main\" | cat"
    # 追加したいコマンドをここに追加
)

for cmd in "${commands[@]}"
do
    # myshellの出力結果をmyshell.outに保存
    ./minishell -c "$cmd" > minishell.out

    # bashの出力結果をbash.outに保存
    bash -c "$cmd" > bash.out

    # 両者の出力結果を比較して差異があれば表示
    diff minishell.out bash.out
    if [ $? -eq 0 ]
    then
        echo "minishellとbashの出力結果は一致しています"
    else
        echo "minishellとbashの出力結果が一致しません"
    fi
done