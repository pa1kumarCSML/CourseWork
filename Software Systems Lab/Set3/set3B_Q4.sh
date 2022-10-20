case $1 in
"-p")
	echo "----------------------------"

	ps -eo pid,ppid,cmd,%mem,%cpu --sort=-%mem | head

	echo "----------------------------"

;;

"-m")
	#findmnt -lo source,target,fstype,label,options,used
	echo "----------------------------"

	df -h --output=source,target

	echo "----------------------------"

;;

"-f")
	#files created in last 1hr
	echo "----------------------------"

	find ./ -cmin -60 -type f | sort -rh | head -5

	echo "----------------------------"

;;

*)

	#Disks whoes mem use >=30

	df -h | awk '{ if ($5 >= 30) { print $5 , $1} }'

;;
esac
