#include <stdio.h>
#include <string.h>
#include <time.h>
 
#define MAX 100

int findEmpByID(char id[]);
void genLogID(char logId[]);
int checked(char empId[], int d , int m , int y);
int futureDate(int d , int m , int y); 

void addEmployee();       // F01
void updateEmployee();    // F02
void deleteEmployee();    // F03
void printList();         // F04
void searchByName();      // F05
void sortByBasesalary();  // F06
void checkIn();           // F07 
void viewTimesheet();     // F08 

// Ham ho tro
void addSampleList();

int showMenu() {
    int choice;

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
    scanf("%d", &choice);
	getchar(); 
    return choice;
}

int main (){
	int choice ;
	addSampleList();
	do {
		choice = showMenu();
		
	    switch (choice) {
	        case 1: addEmployee(); break;
	        case 2: updateEmployee(); break;
	        case 3: deleteEmployee(); break;
	        case 4: printList(); break;
			case 5: searchByName(); break;
			case 6: sortByBasesalary(); break;
			case 7: checkIn(); break;
			case 8: viewTimesheet(); break;
			case 9: 
				printf("Thoat chuong trinh !\n");
				break;
				
			default : printf("Lua chon khong hop le !\n"); 
	    }
	    //dung switch case de chay tuong ung voi lua chon nguoi dung nhap vao
	}while (choice != 9);
	return 0 ;
}

typedef struct {
char empId[20];
char name[50];
char position[15];
double baseSalary;
int workDay;
} Employee;

typedef struct {
	char logId[20];
	char empId[20];
	char date[20];
	char status[10];
}TimeSheet;

Employee employees[MAX];
int empCount = 0;
TimeSheet timeSheet[MAX];
int timeCount = 0;
//Ham tien ich tim kiem nhan vien bang id 
int findEmpByID(char id[]) {
	for (int i = 0; i < empCount; i++) {
		if (strcmp(employees[i].empId, id) == 0)
		return i;
}
	return -1;
}

void genLogID (char logId[]){ // tu tao ma log moi cho bang cham cong 
	sprintf(logId , "HG%04d" , timeCount + 1);
}

int checked (char empId[], int d, int m, int y) {
    char date[20];
    sprintf(date, "%d/%d/%d", d, m, y);

    for (int i = 0; i < timeCount; i++) {
        if (strcmp(timeSheet[i].empId, empId) == 0 &&strcmp(timeSheet[i].date, date) == 0)
        {
            printf("Nhan vien da cham cong ngay nay truoc do!\n" );
            return 1;
        }
    }
    return 0;
}


int isValidDate(int d , int m , int y) { // ham check xem ngay co dung dinh dang khong 
    int flag = 1 ;
	if(m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12){
		if(d < 1 || d > 31){
			flag = 0 ; 
			printf("Ngay cham cong khong hop le !\n");
		}
	}
	
	if(m == 4 || m == 6 || m == 9 || m == 11){
		if(d < 1 || d > 30){
			flag = 0 ; 
			printf("Ngay cham cong khong hop le !\n");
		}
	}
	
	if(m == 2){
		if((y % 4 == 0 && y % 100 != 0) || y % 400 == 0){
			if(d < 1 || d > 29){
				flag = 0 ;
				printf("Ngay cham cong khong hop le!\n");
			} 
		}else{
			if(d < 1 || d > 28){
				flag = 0 ;
				printf("Ngay cham cong khong hop le!\n");
			}
		}
	}
	
	if(m < 1 || m > 12){
		flag = 0 ;
		printf("Thang cham cong khong hop le !\n");
	} 
	
	if(y < 1900 || y > 2100){
		flag = 0 ;
		printf("Nam cham cong khong hop le !\n");
	}
	return flag ;
}

int futureDate (int d , int m , int y){
	time_t t = time(NULL);
	struct tm current = *localtime(&t);
	
	int cur_d = current.tm_mday;
	int cur_m = current.tm_mon + 1;
	int cur_y = current.tm_year + 1900 ; 
	if (y > cur_y){
		return 1 ;
	}
	
	if(y == cur_y && m > cur_m){
		return 1 ; 
	}
	
	if(y == cur_y && m == cur_m && d > cur_d){
		return 1 ;
	}
	return 0 ; 
}


// F01 - Them nhan vien moi 
void addEmployee() {
if (empCount >= MAX) {
printf("Danh sach nhan vien day!\n");
return;
}
Employee e;

while (getchar() != '\n');//clear buffer , tranh bi skip 

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
    	while(getchar() != '\n');
        break;
    }
} while (1);

    int choose ;
    printf("1. Mac dinh Workday = 0 \n");
    printf("2. Yeu cau nguoi dung nhap Workday \n");
    printf("Chon cach hien thi :");
    scanf("%d" , &choose);
    if(choose != 1 && choose != 2){
    	printf("Lua chon khong hop le !\n");
    	return ;
	}
    if(choose == 1){
    	e.workDay = 0 ;
    	printf("Workday = 0\n");
	}else{
		do {
			printf("Nhap ngay cong : ");
			if(scanf("%d" , &e.workDay) != 1 || e.workDay < 0){
				printf("Ngay cong khong hop le !\n");
				while(getchar() != '\n');
			}else {
				break ;
			}
		}while(1);
	}

employees[empCount++] = e;
printf("Them nhan vien thanh cong!\n");
}

//F02 - Cap nhat ho so nhan vien
void updateEmployee() {
char id[20];
while (getchar() != '\n');//clear buffer , tranh bi skip

printf("Nhap ma NV can cap nhat: ");
fgets(id, sizeof(id), stdin);
id[strcspn(id, "\n")] = '\0';

int idx = findEmpByID(id);
if (idx == -1) {
    printf("Khong tim thay nhan vien co ma %s!\n" , id);// tao bien voi ham tien ich da tao 
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
    	while(getchar() != '\n');
        break;
    }
} while (1);

printf("Cap nhat nhan vien thanh cong!\n");
}

//F03 - Quan li nhan vien : Sa thai / Nghi viec 
void deleteEmployee() {
    char id[20];
    while (getchar() != '\n'); // clear buffer tranh bi skip

    printf("Nhap ma NV muon xoa: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    int idx = findEmpByID(id);  // tim nhân viên
    if (idx == -1) {
        printf("Khong tim thay nhan vien co ma %s!\n", id);
        return;
    }

    int confirm; 
	printf("Xac nhan xoa nhan vien (1: Co, 0: Khong)? ");// bien xac nhan xem co muon xoa nhan vien khong ?
	scanf("%d" , &confirm);
	while(getchar() != '\n');
	
	if(confirm == 1){
		for (int i = idx ; i < empCount - 1 ; i++){
			employees[i] = employees[i + 1];
		}
		empCount -- ; 
		printf("Da xoa nhan vien co ma %s thanh cong !\n" , id);
	}else {
		printf("Huy xoa nhan vien ! \n");
	}
}


// F04 - Hien thi danh sach nhan vien 
void printList() {
    if (empCount == 0) {
        printf("Danh sach nhan vien hien dang trong!\n");
        return;
    }

    int perPage = 5 ;
    int totalPage = (empCount + perPage - 1) / perPage;
    int page = 1;  // bat dau xem tu trang 1

    printf("Danh sach co %d trang.\n", totalPage);
    printf("Ban se lan luot nhap cac trang tu 1 den %d.\n\n", totalPage);

    while (page <= totalPage) {
        int p;

        // Nhap dung so trang hien tai
        while (1) {
            printf("Nhap trang : ");

            if (scanf("%d", &p) != 1) {
                printf("Dinh dang khong hop le! Vui long nhap so.\n");
                while (getchar() != '\n');
                continue;
            }
            while (getchar() != '\n'); // clear buffer

            if (p != page) {
                printf("Ban phai nhap dung so trang: %d\n", page);
                continue;
            }

            break;
        }

        // Hien thi trang do
        int start = (page - 1) * perPage;
        int end = start + perPage;
        if (end > empCount) end = empCount;

        printf("\n=== TRANG %d / %d ===\n", page, totalPage);

        printf("+----+------------+----------------------+---------------+------------+----------+\n");
        printf("| STT| Ma NV      | Ten NV               | Chuc vu       | Luong      | Ngay cong|\n");
        printf("+----+------------+----------------------+---------------+------------+----------+\n");

        for (int i = start; i < end; i++) {
            printf("| %2d | %-10s | %-20s | %-10s    | %10.2lf | %8d |\n",
                   i + 1,
                   employees[i].empId,
                   employees[i].name,
                   employees[i].position,
                   employees[i].baseSalary,
                   employees[i].workDay);
        }
        printf("+----+------------+----------------------+---------------+------------+----------+\n\n");

        page++; // chuyen sang trang tiep theo
    }
}

//F05 - Tim kiem nhan vien theo ten 
void searchByName() {
char name[50];
while(getchar() != '\n'); // clear buffer tranh bi skip

while(1) {
	printf("Nhap ten nhan vien can tim: ");
	fgets(name, sizeof(name), stdin);
	name[strcspn(name, "\n")] = '\0';
	
	if(strlen(name) == 0){
		printf("Ten nhan vien can tim khong duoc de trong !\n");
	}else {
		break;
	}
}

int found = 0; // Tao bien co
for (int i = 0; i < empCount; i++) {
    if (strstr(employees[i].name, name) != NULL) { // dung ham strstr kiem tra chuoi name co la chuoi con cua employees[i].name khong ?
        printf("\nMa NV: %s\nTen NV: %s\nChuc vu: %s\nLuong: %.2lf\nNgay cong: %d\n",
               employees[i].empId, employees[i].name, employees[i].position,
               employees[i].baseSalary, employees[i].workDay);
        found = 1; // Bien co duoc bat len
    }
}
if (!found)
    printf("Khong tim thay nhan vien!\n"); // khac bien co thi bao khong tim thay nhan vien 
}

//F06 - Sap xep nhan vien theo luong co ban tang dan / giam dan
void sortByBasesalary() {
    if (empCount == 0) {
        printf("Danh sach nhan vien hien tai dang trong!\n");
        return;
    }

    int option;
    while (1) {
        printf("1. Tang dan\n");
        printf("2. Giam dan\n");
        printf("Chon cach sap xep: "); //yeu cau nguoi dung chon 1 trong 2 option sap xep
        scanf("%d", &option);
        while (getchar() != '\n');

        if (option == 1 || option == 2) break;
        printf("Lua chon khong hop le! Hay nhap lai.\n");
    }
    for (int i = 0; i < empCount - 1; i++) {
        for (int j = i + 1; j < empCount; j++) {

            int swap = 0;

            if (option == 1 && employees[i].baseSalary > employees[j].baseSalary)
                swap = 1;

            if (option == 2 && employees[i].baseSalary < employees[j].baseSalary)
                swap = 1;

            if (swap) {
                Employee temp = employees[i];
                employees[i] = employees[j];
                employees[j] = temp;
            }
        }
    }
    if (option == 1)
        printf("Da sap xep tang dan theo luong thanh cong!\n");
    else
        printf("Da sap xep giam dan theo luong thanh cong!\n");
}

//F07 - Cham cong 
void checkIn (){
	char inpId[20];
	int index = -1 ;
	
	do {
		printf("Nhap ma nhan vien can kiem tra cham cong : ");
		fgets(inpId , 20 , stdin);
		inpId[strcspn(inpId , "\n")] = '\0';
		index = findEmpByID(inpId);
		if(index == -1){
			printf("Khong tim thay nhan vien co ma %s!\n" , inpId);
		}
	}while(index == -1);
	
	printf("Thong tin nhan vien\n");
	printf("Ma nhan vien : %s\n" , employees[index].empId);
	printf("Ten nhan vien : %s\n" , employees[index].name);
	printf("Chuc vu : %s\n" , employees[index].position);
	
	int d , m , y ;
	do {
		printf("Nhap ngay cham cong (dd/mm/yyyy) : ");
		if(scanf("%d/%d/%d" , &d , &m , &y) != 3){
			printf("Nhap sai dinh dang ! Nhap lai !\n");
			while(getchar() != '\n');
			continue ; 
		}
	}while(isValidDate(d,m,y) == 0);
	
	if(futureDate(d,m,y)){
		printf("Khong duoc cham cong trong tuong lai ! \n");
		return ; 
	}
	
	if(checked(inpId , d, m, y) == 1){
		return ;
	}
	
	genLogID(timeSheet[timeCount].logId);
	strcpy(timeSheet[timeCount].empId , inpId);
	sprintf(timeSheet[timeCount].date , "%d/%d/%d" , d , m , y);
	strcpy(timeSheet[timeCount].status , "Di lam");
	timeCount ++ ;
	employees[index].workDay++ ;
	printf("Da cham cong cho nhan vien co ma %s vao ngay %d/%d/%d thanh cong !\n" , inpId , d , m , y);
}

void viewTimesheet() {
    char inpId[20];
    int index = -1;

    // Nhap ma NV hop le
    do {
        printf("Nhap ID nhan vien muon xem bang cham cong: ");
        fgets(inpId, 20, stdin);
        inpId[strcspn(inpId, "\n")] = '\0';
        index = findEmpByID(inpId);
        if(index == -1){
            printf("Khong tim thay nhan vien co ma %s!\n", inpId);
        }
    } while(index == -1);

    int d, m, y;
    do {
        printf("Nhap ngay ket thuc (dd/mm/yyyy): ");
        if(scanf("%d/%d/%d", &d, &m, &y) != 3){
            printf("Nhap sai dinh dang! Nhap lai!\n");
            while(getchar() != '\n');
            continue;
        }
    } while(!isValidDate(d,m,y) || futureDate(d,m,y));
    while(getchar() != '\n');

    printf("--------------------------------------------\n");
    printf("          BANG CHAM CONG NHAN VIEN          \n");
    printf("--------------------------------------------\n");
    printf(" Ma NV     : %s\n", employees[index].empId);
    printf(" Ho va Ten : %s\n", employees[index].name);
    printf(" Chuc vu   : %s\n", employees[index].position);
    printf("--------------------------------------------\n");
    printf("| %-10s | %-15s |\n", "NGAY", "TRANG THAI");
    printf("|------------|-----------------|\n");

    int countWorkDay = 0;
    int toggle = 1; // dung de xen ke Di lam / Nghi cho ngay chua co log

    for(int day = 1; day <= d; day++){
        char dateStr[20];
        sprintf(dateStr, "%d/%d/%d", day, m, y);
        int found = 0;

        // Kiem tra xem co log cham cong khong
        for(int i = 0; i < timeCount; i++){
            if(strcmp(timeSheet[i].empId, inpId) == 0 &&
               strcmp(timeSheet[i].date, dateStr) == 0){
                printf("| %-10s | %-15s |\n", dateStr, timeSheet[i].status);
                if(strcmp(timeSheet[i].status,"Di lam") == 0) countWorkDay++;
                found = 1;
                break;
            }
        }

        if(!found){
            // Neu chua co log, hien thi xen ke Di lam/Nghi
            if(toggle){
                printf("| %-10s | %-15s |\n", dateStr, "Di lam");
                countWorkDay++;
            } else {
                printf("| %-10s | %-15s |\n", dateStr, "Nghi");
            }
            toggle = !toggle; // doi trang thai cho ngay tiep theo
        }
    }

    printf("--------------------------------------------\n");
    printf("Tong so ngay di lam: %d\n", countWorkDay);
    printf("--------------------------------------------\n");
    getchar();
}

void addSampleList() {  // tao 1 danh sach nhan vien co san 
Employee e1 = {"HG001", "Tran Minh Duc", "Quan li", 2000, 5};
Employee e2 = {"HG002", "Phung Duy Dat", "Nhan vien", 1000, 3};
Employee e3 = {"HG003", "Nguyen Minh Hieu", "Giam doc", 5000, 8};
Employee e4 = {"HG004", "Tang Hieu Thanh", "Chu tich", 10000 , 11};
employees[empCount++] = e1;
employees[empCount++] = e2;
employees[empCount++] = e3;
employees[empCount++] = e4;
}
