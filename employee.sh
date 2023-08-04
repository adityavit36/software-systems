#!/bin/bash
declare -A employees

function add_employee_record() {
    echo "Enter Employee Name:"
    read name
    echo "Enter Employee Number:"
    read emp_number
    echo "Enter Telephone Number:"
    read phone_number
    employees["$emp_number"]="$name,$phone_number"
    echo "Employee Record added successfully!"
}

function delete_employee_record() {
    echo "Enter Employee Number to delete:"
    read emp_number

    if [[ ${employees["$emp_number"]} ]]; then
        unset employees["$emp_number"]
        echo "Employee Record deleted successfully!"
    else
        echo "Employee Number not found in the record!"
    fi
}

function search_employee_record() {
    echo "Enter Employee Number to search:"
    read emp_number

    if [[ ${employees["$emp_number"]} ]]; then
        echo "Employee Name: ${employees["$emp_number"]%,*}"
        echo "Telephone Number: ${employees["$emp_number"]#*,}"
    else
        echo "Employee Number not found in the record!"
    fi
}

function list_all_records() {
    if [[ ${#employees[@]} -eq 0 ]]; then
        echo "Employee Record is empty!"
    else
        echo "Employee Records:"
        for emp_number in "${!employees[@]}"; do
            echo "Employee Number: $emp_number"
            echo "Employee Name: ${employees["$emp_number"]%,*}"
            echo "Telephone Number: ${employees["$emp_number"]#*,}"
            echo "-------------------------"
        done
    fi
}

function sort_records() {
    if [[ ${#employees[@]} -eq 0 ]]; then
        echo "Employee Record is empty!"
    else
        echo "Sorted Employee Records:"
        for emp_number in $(echo "${!employees[@]}" | tr ' ' '\n' | sort); do
            echo "Employee Number: $emp_number"
            echo "Employee Name: ${employees["$emp_number"]%,*}"
            echo "Telephone Number: ${employees["$emp_number"]#*,}"
            echo "-------------------------"
        done
    fi
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

          
