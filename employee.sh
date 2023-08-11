#!/bin/bash


function add_employee_record() {
   read -p "Enter Employee Name: " name
    read -p "Enter Employee Number: " emp_number
    read -p "Enter Telephone Number: " telephone
    # Check if the employee number already exists
    if grep -q "^.*:$emp_number:.*$" employee_records.txt; then
        echo "Employee Number $emp_number already exists. Cannot create duplicate records."
    else
        # Append the new record to the file
        echo "$name:$emp_number:$telephone" >> employee_records.txt
        echo "Employee Record created successfully!"
    fi
}

function delete_employee_record() {
    read -p "Enter the Employee Number to delete: " emp_number
    # Use temporary file to store the updated records
    grep -v "^.*:$emp_number:.*$" employee_records.txt > temp.txt
    mv temp.txt employee_records.txt
    echo "Employee Record deleted successfully!"
}

function search_employee_record() {
    read -p "Enter the Employee Number to search: " emp_number
    grep "^.*:$emp_number:.*$" employee_records.txt
}

function list_all_records() {
    sed 's/:/ /g' employee_records.txt
}

function sort_records() {
    # sort -t ':' -k 2 employee_records.txt > temp.txt
    sort -t ':' -k2n employee_records.txt > temp.txt
    mv temp.txt employee_records.txt
    echo "Record Sorted Successfully!!!"
}

while true; do
    echo "Employee Management Record" 
    echo "Menu"
    echo "1. Add Employee Record"
    echo "2. Delete Employee Record"
    echo "3. Search Employee Record"
    echo "4. List All Records"
    echo "5. Sort Records"
    echo "6. Exit"

    read -p "Enter Your Choice:(1-6) " choice
    case $choice in
	    1) add_employee_record
		    ;;
	    2) delete_employee_record
		    ;;
	    3) search_employee_record
		    ;;
	    4) list_all_record
		    ;;
	    5) sort_records
		    ;;
	    6) echo "Exiting..."
		    exit 0 ;;
    esac
    read -n 1 -s -r -p "Press any key "
    done 

          
