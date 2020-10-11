#!/bin/bash

#lower bound for employee id 
eid=37101

#function to insert a record
accept() {
	eid=`expr $eid + 1`
	while true
	  do
		read -p "Enter employee name : " name
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
	  	read -p "Enter department(finance, marketing, production) : " dept
		if [ -z "$dept" ]
		then 
		    echo 'Inputs cannot be blank please try again!'
		elif [[ "$dept" =~ ^[a-zA-Z]+$ ]]
		then 
			break
		else
			echo "Input should contain only alphabets"
		fi
	done
	
	while true
	  do
		read -p "Enter designation : " desg
		if [ -z "$desg" ]
		then 
		    echo 'Inputs cannot be blank please try again!'
		elif [[ "$desg" =~ ^[a-zA-Z]+$ ]]
		then 
			break
		else
			echo "Input should contain only alphabets"
		fi 
	done
	
	while true
	  do
		read -p "Enter salary : " sal
		if [ -z "$sal" ]
		then 
		    echo 'Inputs cannot be blank please try again!'
		elif [[ "$sal" =~ ^[0-9]+$ ]]
		then 
			break
		else
			echo "Input should contain only numbers"
		fi 
	done
	
	da=`echo "$sal * 0.5" | bc` 
	hra=`echo "$sal * 0.2" | bc`
	gross=`echo "$sal + $da + $hra" | bc` 
	
	echo "$eid $name $dept $desg $sal $da $hra $gross" >> $1
	echo "Record Inserted sucessfully"
}

#display function to display report department wise, salary wise and designation wise
display() {
	if [ -f "$1" ]
    	then
		printf "\n1. Department-wise Report\n2. Salary-wise Report\n3. Designation-wise report\n4. Entire Report\n"
        	read -p "Enter your choice : " ch1
        	case $ch1 in
        	
        	1) while true
		   do
			read -p "Enter department : " temp
			if [ -z "$temp" ]
			then 
			    echo 'Inputs cannot be blank please try again!'
			elif [[ "$temp" =~ ^[a-zA-Z]+$ ]]
			then 
				break
			else
				echo "Input should contain only alphabets"
			fi 
		   done
        	   echo ""
		   echo "--------------------------------------------------------------------------------"
		   echo "EMP ID  NAME     DEPARTMENT  DESIGNATION  SALARY  DA      HRA      GROSS SALARY"
		   echo "--------------------------------------------------------------------------------"
		   grep -w "$temp" $1 ;;
        	2)while true
		  do
			read -p "Enter salary : " temp
			if [ -z "$temp" ]
			then 
			    echo 'Inputs cannot be blank please try again!'
			elif [[ "$temp" =~ ^[0-9]+$ ]]
			then 
				break
			else
				echo "Input should contain only numbers"
			fi 
		   done
        	   echo ""
		   echo "--------------------------------------------------------------------------------"
		   echo "EMP ID  NAME     DEPARTMENT  DESIGNATION  SALARY  DA      HRA      GROSS SALARY"
		   echo "--------------------------------------------------------------------------------"
		   grep "$temp" $1 ;;
        	3) while true
		   do
			read -p "Enter designation : " temp
			if [ -z "$temp" ]
			then 
			    echo 'Inputs cannot be blank please try again!'
			elif [[ "$temp" =~ ^[a-zA-Z]+$ ]]
			then 
				break
			else
				echo "Input should contain only alphabets"
			fi 
		   done
        	   echo ""
		   echo "--------------------------------------------------------------------------------"
		   echo "EMP ID  NAME     DEPARTMENT  DESIGNATION  SALARY  DA      HRA      GROSS SALARY"
		   echo "--------------------------------------------------------------------------------"
		   grep "$temp" $1 ;;
        	4) echo ""
		   echo "--------------------------------------------------------------------------------"
		   echo "EMP ID  NAME     DEPARTMENT  DESIGNATION  SALARY  DA      HRA      GROSS SALARY"
		   echo "--------------------------------------------------------------------------------"
		   while read -ra line
		   do
				printf "%6d  %6s  %10s  %10s  %6d  %6.2f  %6.2f  %6.2f\n" ${line[0]}  ${line[1]}  ${line[2]}  ${line[3]}  ${line[4]}  ${line[5]}  ${line[6]}  ${line[7]}
		   done < $1
		   echo "";;
        	*) echo "Invalid Option";;
        	esac

	fi
}

#function to search a record
search(){
	while true
	  do
		read -p "Enter the employee id to be searched : " key
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

#function to modify a record
modify() {
	while true
	  do
		read -p "Enter the employee id to be modified : " key
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
	accept $1
	echo "Record modified sucessfully"
}

#function to delete a record
delete() {
	while true
	  do
		read -p "Enter the employee id to be deleted : " key
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

#main program begins
read -p "Enter filename : " fn

while true
do
	printf "\n*****MENU:*****\n1. Accept employee information\n2. Display employee information\n3. Search an employee\n4. Delete employee record\n5. Modify employee record\n6.Exit\nEnter your choice : "
	read ch
	case $ch in
	1)accept $fn;;
	
	2)display $fn;;
	
	3)search $fn;;
	
	4)delete $fn ;;
	
	5)modify $fn ;;
	
	6) exit;;
	
	*)Invalid option;;
	esac
done
