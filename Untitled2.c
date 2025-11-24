#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
char empId[20];
char name[50];
char position[15];
double baseSalary;
int workDay;
} Employee;

Employee employees[MAX];
int empCount = 0;

int findEmpByID(char id[]) {
for (int i = 0; i < empCount; i++) {
if (strcmp(employees[i].empId, id) == 0)
return i;
}
return -1;
}

void addEmployee() {
if (empCount >= MAX) {
printf("Danh sach nhan vien day!\n");
return;
}
Employee e;

while (getchar() != '\n');

do {
    printf("Nhap ma nhan vien: ");
    fgets(e.empId, sizeof(e.empId), stdin);
    e.empId[strcspn(e.empId, "\n")] = '\0';
    if (strlen(e.empId) == 0)
        printf("Ma nhan vien khong duoc rong. Nhap lai!\n");
    else if (findEmpByID(e.empId) != -1)
        printf("Ma nhan vien da ton tai. Nhap lai!\n");
    else
        break;
} while (1);

do {
    printf("Nhap ten nhan vien: ");
    fgets(e.name, sizeof(e.name), stdin);
    e.name[strcspn(e.name, "\n")] = '\0';
    if (strlen(e.name) == 0)
        printf("Ten nhan vien khong duoc rong. Nhap lai!\n");
    else
        break;
} while (1);

do {
    printf("Nhap chuc vu: ");
    fgets(e.position, sizeof(e.position), stdin);
    e.position[strcspn(e.position, "\n")] = '\0';
    if (strlen(e.position) == 0)
        printf("Chuc vu khong duoc rong. Nhap lai!\n");
    else
        break;
} while (1);

do {
    printf("Nhap luong co ban: ");
    if (scanf("%lf", &e.baseSalary) != 1 || e.baseSalary <= 0) {
        printf("Luong khong hop le. Nhap lai!\n");
        while (getchar() != '\n');
    } else {
        while (getchar() != '\n');
        break;
    }
} while (1);

do {
    printf("Nhap ngay cong: ");
    if (scanf("%d", &e.workDay) != 1 || e.workDay < 0) {
        printf("Ngay cong khong hop le. Nhap lai!\n");
        while (getchar() != '\n');
    } else {
        while (getchar() != '\n');
        break;
    }
} while (1);

employees[empCount++] = e;
printf("Them nhan vien thanh cong!\n");
}

void updateEmployee() {
char id[20];
while (getchar() != '\n');

printf("Nhap ma NV can cap nhat: ");
fgets(id, sizeof(id), stdin);
id[strcspn(id, "\n")] = '\0';

int idx = findEmpByID(id);
if (idx == -1) {
    printf("Khong tim thay nhan vien!\n");
    return;
}

do {
    printf("Nhap chuc vu moi: ");
    fgets(employees[idx].position, sizeof(employees[idx].position), stdin);
    employees[idx].position[strcspn(employees[idx].position, "\n")] = '\0';
    if (strlen(employees[idx].position) == 0)
        printf("Chuc vu khong duoc rong. Nhap lai!\n");
    else
        break;
} while (1);

do {
    printf("Nhap luong co ban moi: ");
    if (scanf("%lf", &employees[idx].baseSalary) != 1 || employees[idx].baseSalary <= 0) {
        printf("Luong khong hop le. Nhap lai!\n");
        while (getchar() != '\n');
    } else {
        while (getchar() != '\n');
        break;
    }
} while (1);

printf("Cap nhat nhan vien thanh cong!\n");
}

void deleteEmployee() {
char id[20];
while (getchar() != '\n');

printf("Nhap ma NV muon xoa: ");
fgets(id, sizeof(id), stdin);
id[strcspn(id, "\n")] = '\0';

int idx = findEmpByID(id);
if (idx == -1) {
    printf("Khong tim thay nhan vien!\n");
    return;
}

int confirm;
printf("Xac nhan xoa nhan vien (1: Co, 0: Khong)? ");
scanf("%d", &confirm);
while (getchar() != '\n');

if (confirm == 1) {
    for (int i = idx; i < empCount - 1; i++)
        employees[i] = employees[i + 1];
    empCount--;
    printf("Da xoa nhan vien!\n");
} else {
    printf("Huy xoa nhan vien!\n");
}
}

void printList() {
if (empCount == 0) {
printf("Danh sach trong!\n");
return;
}

for (int i = 0; i < empCount; i++) {
    printf("\nNhan vien %d:\n", i + 1);
    printf("Ma NV: %s\n", employees[i].empId);
    printf("Ten NV: %s\n", employees[i].name);
    printf("Chuc vu: %s\n", employees[i].position);
    printf("Luong co ban: %.2lf\n", employees[i].baseSalary);
    printf("Ngay cong: %d\n", employees[i].workDay);
}
}

void searchByName() {
char name[50];
printf("Nhap ten nhan vien can tim: ");
fgets(name, sizeof(name), stdin);
name[strcspn(name, "\n")] = '\0';

int found = 0;
for (int i = 0; i < empCount; i++) {
    if (strstr(employees[i].name, name) != NULL) {
        printf("\nMa NV: %s\nTen NV: %s\nChuc vu: %s\nLuong: %.2lf\nNgay cong: %d\n",
               employees[i].empId, employees[i].name, employees[i].position,
               employees[i].baseSalary, employees[i].workDay);
        found = 1;
    }
}
if (!found)
    printf("Khong tim thay nhan vien!\n");
}

void addSampleList() {
Employee e1 = {"HG001", "Tran Minh Duc", "Quan li", 2000, 5};
Employee e2 = {"HG002", "Phung Duy Dat", "Nhan vien", 1000, 3};
Employee e3 = {"HG003", "Nguyen Minh Hieu", "Pho giam doc", 5000, 8};
employees[empCount++] = e1;
employees[empCount++] = e2;
employees[empCount++] = e3;
}

int main (){
	int choice ;
	addSampleList();
	do {
	    printf("\n+----------Danh sach quan ly nhan vien va cham cong--------+\n");
	    printf("|1. Them moi nhan vien                                     |\n");
	    printf("|2. Cap nhat ho so nhan vien                               |\n");
	    printf("|3. Sa thai / nghi viec                                    |\n");
	    printf("|4. Hien thi danh sach nhan vien                           |\n");
	    printf("|5. Tra cuu thong tin nhan vien                            |\n");
	    printf("|6. Sap xep danh sach nhan vien theo luong co ban          |\n");
	    printf("|7. Cham ngay cong                                         |\n");
	    printf("|8. Xem bang cong                                          |\n");
	    printf("|9. Thoat                                                  |\n");
	    printf("+----------------------------------------------------------+\n");
	
	    printf("Nhap lua chon cua ban : ");
	    scanf("%d" , &choice);
	
	    switch (choice) {
	        case 1: addEmployee(); break;
	        case 2: updateEmployee(); break;
	        case 3: deleteEmployee(); break;
	        case 4: printList(); break;
			case 5: searchByName(); break;
	
	    }
	}while (choice != 9);
	return 0 ;
}
