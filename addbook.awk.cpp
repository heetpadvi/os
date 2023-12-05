address book

//address book

create(){
	echo "Enter name of address book to be created"
	read fname
	res=ls | grep $fname | wc -w

	if [ $res -gt 0 ]
	then
		echo "file is present :: Enter another name "
	else
		echo "File is not present"
		touch $fname
		echo "File is created"
	fi
}
display(){
	echo "Enter name of address book to be displayed"
	read fname
	res=ls | grep $fname | wc -w

	if [ $res -gt 0 ]
	then
		echo "file is present "
		cat $fname
	else
		echo "Error :: File is not present in the directory"

	fi
}
insert(){
	echo "Enter name of address book for insertion:"
	read fname
	res=ls | grep $fname | wc -w

	if [ $res -gt 0 ]
	then
		echo "file is present "
		echo "Enter roll no"
		read  rollno
		rollres=cat $fname | grep $rollno |wc -w

		if [ $rollres -gt 0 ]
		then
			echo "roll no is present"
		else
			echo "roll no is not present"
			echo "Enter name:"
			read name
			record=echo $rollno $name
			echo $record >> $fname
			echo "record is successfully inserted"
		fi

	else
		echo "Error :: File is not present in the directory"

	fi
}
modify(){
	echo "Enter name of address book for modification :"
	read fname
	res=ls | grep $fname | wc -w

	if [ $res -gt 0 ]
	then
		echo "file is present "
		echo "Enter roll no for modification"
		read  rollno
		rollres=cat $fname | grep $rollno |wc -w

		if [ $rollres -gt 0 ]
		then
			echo "roll no is present"
			old=cat $fname |grep $rollno
			echo "Old record =$old"

			echo "Enter new name"
			read newname
			new=echo $rollno $newname

			echo "New record = $new"
			sed -i s/"$old"/"$new"/g $fname
			echo "Record is modified"
		else
			echo "roll no is not present"

		fi

	else
		echo "Error :: File is not present in the directory"

	fi
}
delete(){
	echo "Enter name of address book for deletion :"
	read fname
	res=ls | grep $fname | wc -w

	if [ $res -gt 0 ]
	then
		echo "file is present "
		echo "Enter roll no for deletion"
		read  rollno
		rollres=cat $fname | grep $rollno |wc -w

		if [ $rollres -gt 0 ]
		then
			echo "roll no is present"
			old=cat $fname |grep $rollno
			echo "Old record =$old"

			echo "New record = $new"
			sed -i s/"$old"//g $fname
			sed -i /^$/d $fname
			echo "Record is deleted"
		else
			echo "roll no is not present"

		fi

	else
		echo "Error :: File is not present in the directory"

	fi
}


while [ true ]
do
	echo "******** MENU ********"
	echo "1)Create address book"
	echo "2)Display address book"
	echo "3)Insert a record"
	echo "4)Modify a record"
	echo "5)Delete a record"
	echo "6)exit"
	echo "Enter your choice :"
	read choice

	case $choice in
		1) create ;;
		2) display ;;
		3) insert ;;
		4) modify ;;
		5) delete ;;
		6) exit ;;
		*) echo "Wrong Choice entered..."
	esac
done
