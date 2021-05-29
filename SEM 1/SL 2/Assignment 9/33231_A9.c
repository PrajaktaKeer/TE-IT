#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct employee
{
	char emp_name[20];
	int eid, sal;
}employee;

void insert() {
	employee data;
	int file_id, i;
	file_id = open("test.txt", O_RDWR|O_APPEND);

	printf("\nEnter employee name. ");
	scanf("%s", data.emp_name);
	printf("\nEnter employee id. ");
	scanf("%d", &data.eid);
	printf("\nEnter employee salary. ");
	scanf("%d", &data.sal);
	
	write(file_id, &data, sizeof(data));
	close(file_id);
	printf("Record inserted successfully!!\n");
}

void display() {
	employee data;
	int file_id = open("test.txt", O_RDONLY);
	if(!read(file_id, &data, sizeof(data)))
		printf("No entries to display\n");
	else {
		printf("\n---------------------------------------------------------\n");
		printf("\nID\tNAME\t\tSALARY");
		printf("\n---------------------------------------------------------\n");
		do {
			printf("%-5d\t%-10s\t%d\n", data.eid, data.emp_name, data.sal);
		}while(read(file_id, &data, sizeof(data)));
	}
	printf("\n");
}

void delet() {
	employee data;
	int file_id = open("test.txt", O_RDONLY), file_id1 = open("test1.txt", O_CREAT|O_RDWR, 0666), key, flag = 0;
	printf("\nEnter employee ID to be deleted: ");
	scanf("%d", &key);

	while(read(file_id, &data, sizeof(data))) {
		if(data.eid != key)
			write(file_id1, &data, sizeof(data));
		else
			flag = 1;
	}
	if(flag == 1)
		printf("\nRecord delete successfully!\n"); 
	else
		printf("\nRecord not found\n");

	close(file_id);
	close(file_id1);
	remove("test.txt");
	rename("test1.txt", "test.txt");
}

void search() {
	employee data;
	int file_id = open("test.txt", O_RDONLY), key, flag = 0;
	printf("\nEnter employee id to be searched. ");
	scanf("%d", &key);

	while(read(file_id, &data, sizeof(data))) {
		if(data.eid == key) {
			flag = 1;
			break;
		}
	}
	if(flag == 1) {
		printf("\n---------------------------------------------------------\n");
		printf("\nID\tNAME\t\tSALARY");
		printf("\n---------------------------------------------------------\n");
		printf("%-5d\t%-10s\t%d\n", data.eid, data.emp_name, data.sal);

	}
	else
		printf("\nRecord not found\n");

}

void modify() {
	employee data;
	int file_id = open("test.txt", O_RDONLY), file_id1 = open("test1.txt", O_CREAT|O_RDWR, 0666), key, flag = 0;
	printf("\nEnter employee ID to be modified: ");
	scanf("%d", &key);

	while(read(file_id, &data, sizeof(data))) {
		if(data.eid != key)
			write(file_id1, &data, sizeof(data));
		else {
			flag = 1;
			printf("\nEnter new name. ");
			scanf("%s", data.emp_name);
			printf("\nEnter new salary. ");
			scanf("%d", &data.sal);
			write(file_id1, &data, sizeof(data));
		}
	}
	if(flag == 1)
		printf("\nRecord modified successfully!\n"); 
	else
		printf("\nRecord not found\n");

	close(file_id);
	close(file_id1);
	remove("test.txt");
	rename("test1.txt", "test.txt");
}

int main()
{
	int ch;
	do {
		printf("MENU:\n1. Insert a record\n2. View all records\n3. Delete a record\n4. Search a record\n5. Modify a record\n6. Exit\nEnter your choice = ");
		scanf("%d", &ch);
		switch(ch) {
			case 1:
				insert();
				break;
			case 2:
				display();
				break;
			case 3:
				delet();
				break;
			case 4:
				search();
				break;
			case 5:
				modify();
				break;
			case 6:
				printf("\nBye\n");
				return 0;
			default:
				printf("Invalid choice(1 - 6 only).");
		}
	}while(1);
}

