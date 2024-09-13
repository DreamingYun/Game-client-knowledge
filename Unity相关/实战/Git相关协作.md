git回退版本

先查看（git官网提交）要回退的版本号，然后使用reset进行强制回退

git reset --hard <commit ID号> 

git的commit协作

git rebase（变基再合并）

rebase会把当前分支的 commit 放到**公共分支的最后面**,所以叫变基。就好像从公共分支又重新拉出来这个分支一样。例如在子分支提交了commit，然后rebase master（公共分支），会把commit放在master上所有commit的后面（保留分支的commit），然后进行合并（**这有助于保持清晰的提交历史**，并减少不必要的合并提交）

git pull 是进行了获取与合并，默认合并方式是merge，如果加上rebase即命令为git pull --rebase的时候，就会以**rebase的方式进行合并分支**



git merge（直接合并）

会将公共分支master和当前分支的commit合并在一起，形成一个新的commit提交