#!/bin/bash

#setting the range for roll numbers of each division
r9=33101
r10=33201
r11=33301

#function to insert records
insert() {
	  while true
	  do
		read -p "Enter name : " name
		if [ -z "$name" ]
		then 
		    echo 'Inputs cannot be blank please try again!'
		elif [[ "$name" =~ ^[a-zA-Z]+$ ]]
		then 
			break
		else
			echo "Name should contain only alphabets"
		fi 
	  done

	  while true
	  do
		read -p "Enter class(TE) : " class
		if [ -z "$class" ]
		then 
		    echo 'Inputs cannot be blank please try again!'
		elif [[ "$class" =~ ^[a-zA-Z]+$ ]]
		then 
			break
		else
			echo "Input should contain only alphabets"
		fi 
	  done

	  while true
	  do
	  	read -p "Enter division(9, 10, 11) : " div
	  	case $div in
	  		9) rno=$r9
			   r9=`expr $r9 + 1`;;
	  		10)rno=$r10
			   r10=`expr $r10 + 1`;;
	  		11)rno=$r11
			   r11=`expr $r11 + 1`;;
	  		*)echo "Enter valid division(9, 10, 11)"
	  	esac
		if (( $div == 9 || $div == 10 || $div == 11))
	  	then 
	  		break;
	  	fi
	  done

	  while true
	  do
		read -p "Enter marks of 5 subjects : " m1 m2 m3 m4 m5
		if [ -z "$m1" ] | [ -z "$m2" ] | [ -z "$m3" ] | [ -z "$m4" ] | [ -z "$m5" ]
		then 
		    echo 'Inputs cannot be blank please try again!'
		elif [[ "$m1" =~ ^[0-9]+$ ]] & [[ "$m2" =~ ^[0-9]+$ ]] & [[ "$m3" =~ ^[0-9]+$ ]] & [[ "$m4" =~ ^[0-9]+$ ]] & [[ "$m5" =~ ^[0-9]+$ ]] 
 		then 
			break
		else
			echo "Input should contain only numbers"
		fi 
	  done 
	  
	  total=`expr $m1 + $m2 + $m3 + $m4 + $m5`
	  avg=`expr $total / 5`
	  echo "$name $rno $class $div $m1 $m2 $m3 $m4 $m5 $avg" >> $1
	  echo "Record Inserted sucessfully"
}

#display function for subject wise result
display1() {
	echo ""
	echo "-----------------------------------------------------------------------------------"
	echo "Name  Roll No   Class   Div  Subject 1  Subject 2  Subject 3  Subject 4  Subject  5"
	echo "-----------------------------------------------------------------------------------"
	while read -ra line; do
		printf "%4s  %7d  %5s  %3d  " ${line[0]}  ${line[1]}  ${line[2]}  ${line[3]}
		for ((i=4; i <=8; i++))
		do
			if ((${line[i]} >= 40))
			then 
				printf "%9s  " "Passed"
			else 
				printf "%9s  " "Failed"
			fi 
		done
		echo ""
	done < $1
	echo ""
}

#display function for overall result including average and grade
display2() {
	echo ""
	echo "-----------------------------------------------"
	echo "Name  Roll No   Class   Div  Average  Grade"
	echo "-----------------------------------------------"
	while read -ra line; do
		printf "%4s  %7d  %5s  %3d  %7.2f%%" ${line[0]}  ${line[1]}  ${line[2]}  ${line[3]} ${line[9]}
		if ((${line[9]} >= 75))
		then
			printf " Distinction\n"
		elif ((${line[9]} < 75 && ${line[9]} >= 60))
		then
			printf " First Class\n"
		elif ((${line[9]} < 60 && ${line[9]} >= 40))
		then
			printf " Second Class\n"
		else
			printf " Fail\n"
		fi
	done < $1
        echo ""
}

#function to delete a record
delete() {
	  while true
	  do
		read -p "Enter roll no to be deleted : " key
		if [ -z "$key" ]
		then 
		    echo 'Inputs cannot be blank please try again!'
		elif [[ "$key" =~ ^[0-9]+$ ]]
		then 
			break
		else
			echo "Input should contain only numbers"
		fi 
	  done
	  
	  grep -v "$key" $1 >> temp
	  mv temp $1
	  echo "Record Deleted sucessfully"
}

#function to modify a record
modify() {
	  while true
	  do
		read -p "Enter roll no to be deleted : " key
		if [ -z "$key" ]
		then 
		    echo 'Inputs cannot be blank please try again!'
		elif [[ "$key" =~ ^[0-9]+$ ]]
		then 
			break
		else
			echo "Input should contain only numbers"
		fi 
	  done
	  grep -v "$key" $1 >> temp
	  mv temp $1
	  
	  insert $1
	  echo "Record modified sucessfully"
}

#function to search a record
search() {
	flag=0 
	while true
	  do
		read -p "Enter roll no to be deleted : " key
		if [ -z "$key" ]
		then 
		    echo 'Inputs cannot be blank please try again!'
		elif [[ "$key" =~ ^[0-9]+$ ]]
		then 
			break
		else
			echo "Input should contain only numbers"
		fi 
	done

	if grep -w "$key" $1
	then
		echo "Record found"
	else
		echo "Record not found"
	fi
}

#main program begins
read -p "Enter filename : " fn

while true
do
echo -e $"\n*****MENU:*****\n1. Accept student information.\n2. Display student information.\n3. Delete student record.\n4. Modify student record\n5. Search a record\n6. Exit"
read -p "Enter your choice = " ch
case $ch in
	1)insert $fn;;
	
	2)printf "1. Calculate and display subject wise result\n2. Display overall result\nEnter your choice : "
	  read choice
	  
	  case $choice in
		  1)display1 $fn;;
		  2)display2 $fn;;
		  *)echo "Invalid choice";;
	  esac;;

	3)delete $fn;;

	4)modify $fn;;
	
	5)search $fn;;
	
	6)exit;;
	*)echo "Invalid choice";;
esac
done
