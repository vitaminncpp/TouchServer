git reflog |  awk '{ print $1 }' | xargs gitk
