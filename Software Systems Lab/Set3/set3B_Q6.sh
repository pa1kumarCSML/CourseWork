echo "Enter file extension: "
read ext

echo "Enter file name: "
read fname

echo "Enter new file prefix name: "
read prefix

mv  $fname.$ext $prefix$fname.$ext

echo $fname.$ext $prefix$fname.$ext