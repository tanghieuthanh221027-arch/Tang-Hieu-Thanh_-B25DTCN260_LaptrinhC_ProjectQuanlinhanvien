#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAX 100
#define MIN_YEAR 1900
#define MAX_YEAR 2100
#define PER_PAGE_TIMESHEET 7

// ==================== STRUCT DEFINITIONS ====================
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
} TimeSheet;

// ==================== GLOBAL VARIABLES ====================
Employee employees[MAX];
int empCount = 0;
TimeSheet timeSheet[MAX];
int timeCount = 0;

// ==================== FUNCTION DECLARATIONS ====================
// Utility functions
int findEmpByID(char id[]);
void genLogID(char logId[]);
int checked(char empId[], int d, int m, int y);
int isValidDate(int d, int m, int y);
int futureDate(int d, int m, int y);
void clearInputBuffer();
int strcasecmp_custom(const char *s1, const char *s2);

// Main functions
void addEmployee();       // F01
void updateEmployee();    // F02
void deleteEmployee();    // F03
void printList();         // F04
void searchByName();      // F05
void sortByBasesalary();  // F06
void checkIn();           // F07
void viewTimesheet();     // F08

// Helper functions
void addSampleList();
int showMenu();

// ==================== MAIN FUNCTION ====================
int main() {
    int choice;
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
                printf("Thoat chuong trinh!\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (choice != 9);
    
    return 0;
}

// ==================== UTILITY FUNCTIONS ====================
void clearInputBuffer() {
    while (getchar() != '\n');
}

int strcasecmp_custom(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        char c1 = (*s1 >= 'A' && *s1 <= 'Z') ? (*s1 + 32) : *s1;
        char c2 = (*s2 >= 'A' && *s2 <= 'Z') ? (*s2 + 32) : *s2;
        if (c1 != c2) return c1 - c2;
        s1++;
        s2++;
    }
    return (*s1 - *s2);
}

int findEmpByID(char id[]) {
    for (int i = 0; i < empCount; i++) {
        if (strcmp(employees[i].empId, id) == 0)
            return i;
    }
    return -1;
}

void genLogID(char logId[]) {
    sprintf(logId, "HG%04d", timeCount + 1);
}

int checked(char empId[], int d, int m, int y) {
    char date[20];
    sprintf(date, "%02d/%02d/%04d", d, m, y);
    
    for (int i = 0; i < timeCount; i++) {
        if (strcmp(timeSheet[i].empId, empId) == 0 && 
            strcmp(timeSheet[i].date, date) == 0) {
            printf("Nhan vien da cham cong ngay nay truoc do!\n");
            return 1;
        }
    }
    return 0;
}

int isValidDate(int d, int m, int y) {
    int flag = 1;
    
    if (m < 1 || m > 12) {
        flag = 0;
        printf("Thang cham cong khong hop le!\n");
        return flag;
    }
    
    if (y < MIN_YEAR || y > MAX_YEAR) {
        flag = 0;
        printf("Nam cham cong khong hop le!\n");
        return flag;
    }
    
    // Months with 31 days
    if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) {
        if (d < 1 || d > 31) {
            flag = 0;
            printf("Ngay cham cong khong hop le!\n");
        }
    }
    // Months with 30 days
    else if (m == 4 || m == 6 || m == 9 || m == 11) {
        if (d < 1 || d > 30) {
            flag = 0;
            printf("Ngay cham cong khong hop le!\n");
        }
    }
    // February
    else if (m == 2) {
        int isLeapYear = (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
        int maxDay = isLeapYear ? 29 : 28;
        
        if (d < 1 || d > maxDay) {
            flag = 0;
            printf("Ngay cham cong khong hop le!\n");
        }
    }
    
    return flag;
}

int futureDate(int d, int m, int y) {
    time_t t = time(NULL);
    struct tm current = *localtime(&t);
    
    int cur_d = current.tm_mday;
    int cur_m = current.tm_mon + 1;
    int cur_y = current.tm_year + 1900;
    
    if (y > cur_y) return 1;
    if (y == cur_y && m > cur_m) return 1;
    if (y == cur_y && m == cur_m && d > cur_d) return 1;
    
    return 0;
}

// ==================== MENU FUNCTION ====================
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
    
    printf("Nhap lua chon cua ban: ");
    scanf("%d", &choice);
    clearInputBuffer();
    
    return choice;
}

// ==================== MAIN FEATURE FUNCTIONS ====================
// F01 - Them nhan vien moi
void addEmployee() {
    if (empCount >= MAX) {
        printf("Danh sach nhan vien day!\n");
        return;
    }
    
    Employee e;
    
    // Nhap ma nhan vien
    do {
        printf("Nhap ma nhan vien: ");
        fgets(e.empId, sizeof(e.empId), stdin);
        e.empId[strcspn(e.empId, "\n")] = '\0';
        
        if (strlen(e.empId) == 0) {
            printf("Ma nhan vien khong duoc rong. Nhap lai!\n");
        } else if (findEmpByID(e.empId) != -1) {
            printf("Ma nhan vien da ton tai. Nhap lai!\n");
        } else {
            break;
        }
    } while (1);
    
    // Nhap ten nhan vien
    do {
        printf("Nhap ten nhan vien: ");
        fgets(e.name, sizeof(e.name), stdin);
        e.name[strcspn(e.name, "\n")] = '\0';
        
        if (strlen(e.name) == 0) {
            printf("Ten nhan vien khong duoc rong. Nhap lai!\n");
        } else {
            break;
        }
    } while (1);
    
    // Nhap chuc vu
    do {
        printf("Nhap chuc vu: ");
        fgets(e.position, sizeof(e.position), stdin);
        e.position[strcspn(e.position, "\n")] = '\0';
        
        if (strlen(e.position) == 0) {
            printf("Chuc vu khong duoc rong. Nhap lai!\n");
        } else {
            break;
        }
    } while (1);
    
    // Nhap luong co ban
    do {
        printf("Nhap luong co ban: ");
        if (scanf("%lf", &e.baseSalary) != 1 || e.baseSalary <= 0) {
            printf("Luong khong hop le. Nhap lai!\n");
            clearInputBuffer();
        } else {
            clearInputBuffer();
            break;
        }
    } while (1);
    
    // Nhap ngay cong
    int choose;
    printf("1. Mac dinh Workday = 0\n");
    printf("2. Yeu cau nguoi dung nhap Workday\n");
    printf("Chon cach hien thi: ");
    scanf("%d", &choose);
    clearInputBuffer();
    
    if (choose != 1 && choose != 2) {
        printf("Lua chon khong hop le!\n");
        return;
    }
    
    if (choose == 1) {
        e.workDay = 0;
        printf("Workday = 0\n");
    } else {
        do {
            printf("Nhap ngay cong: ");
            if (scanf("%d", &e.workDay) != 1 || e.workDay < 0) {
                printf("Ngay cong khong hop le!\n");
                clearInputBuffer();
            } else {
                clearInputBuffer();
                break;
            }
        } while (1);
    }
    
    employees[empCount++] = e;
    printf("Them nhan vien thanh cong!\n");
}

// F02 - Cap nhat ho so nhan vien
void updateEmployee() {
    char id[20];
    
    printf("Nhap ma NV can cap nhat: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';
    
    int idx = findEmpByID(id);
    if (idx == -1) {
        printf("Khong tim thay nhan vien co ma %s!\n", id);
        return;
    }
    
    // Cap nhat chuc vu
    do {
        printf("Nhap chuc vu moi: ");
        fgets(employees[idx].position, sizeof(employees[idx].position), stdin);
        employees[idx].position[strcspn(employees[idx].position, "\n")] = '\0';
        
        if (strlen(employees[idx].position) == 0) {
            printf("Chuc vu khong duoc rong. Nhap lai!\n");
        } else {
            break;
        }
    } while (1);
    
    // Cap nhat luong co ban
    do {
        printf("Nhap luong co ban moi: ");
        if (scanf("%lf", &employees[idx].baseSalary) != 1 || 
            employees[idx].baseSalary <= 0) {
            printf("Luong khong hop le. Nhap lai!\n");
            clearInputBuffer();
        } else {
            clearInputBuffer();
            break;
        }
    } while (1);
    
    printf("Cap nhat nhan vien thanh cong!\n");
}

// F03 - Sa thai / Nghi viec
void deleteEmployee() {
    char id[20];
    
    printf("Nhap ma NV muon xoa: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';
    
    int idx = findEmpByID(id);
    if (idx == -1) {
        printf("Khong tim thay nhan vien co ma %s!\n", id);
        return;
    }
    
    // Dich mang de xoa phan tu
    for (int i = idx; i < empCount - 1; i++) {
        employees[i] = employees[i + 1];
    }
    
    empCount--;
    printf("Da xoa nhan vien co ma %s thanh cong!\n", id);
}

// F04 - Hien thi danh sach nhan vien
void printList() {
    if (empCount == 0) {
        printf("Danh sach nhan vien hien dang trong!\n");
        return;
    }
    
    int perPage = 1;
    int totalPage = (empCount + perPage - 1) / perPage;
    int page = 1;
    
    printf("Danh sach co %d trang.\n", totalPage);
    printf("Ban se lan luot nhap cac trang tu 1 den %d.\n\n", totalPage);
    
    while (page <= totalPage) {
        int p;
        
        // Nhap dung so trang hien tai
        while (1) {
            printf("Nhap trang: ");
            
            if (scanf("%d", &p) != 1) {
                printf("Dinh dang khong hop le! Vui long nhap so.\n");
                clearInputBuffer();
                continue;
            }
            clearInputBuffer();
            
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
            printf("| %2d | %-10s | %-20s | %-13s | %10.2lf | %8d |\n",
                   i + 1,
                   employees[i].empId,
                   employees[i].name,
                   employees[i].position,
                   employees[i].baseSalary,
                   employees[i].workDay);
        }
        printf("+----+------------+----------------------+---------------+------------+----------+\n\n");
        
        page++;
    }
}

// F05 - Tim kiem nhan vien theo ten
void searchByName() {
    char name[50];
    
    while (1) {
        printf("Nhap ten nhan vien can tim: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';
        
        if (strlen(name) == 0) {
            printf("Ten nhan vien can tim khong duoc de trong!\n");
        } else {
            break;
        }
    }
    
    int found = 0;
    for (int i = 0; i < empCount; i++) {
        if (strstr(employees[i].name, name) != NULL) {
            printf("\nMa NV: %s\n", employees[i].empId);
            printf("Ten NV: %s\n", employees[i].name);
            printf("Chuc vu: %s\n", employees[i].position);
            printf("Luong: %.2lf\n", employees[i].baseSalary);
            printf("Ngay cong: %d\n\n", employees[i].workDay);
            found = 1;
        }
    }
    
    if (!found) {
        printf("Khong tim thay nhan vien!\n");
    }
}

// F06 - Sap xep nhan vien theo luong co ban
void sortByBasesalary() {
    if (empCount == 0) {
        printf("Danh sach nhan vien hien tai dang trong!\n");
        return;
    }
    
    int option;
    while (1) {
        printf("1. Tang dan\n");
        printf("2. Giam dan\n");
        printf("Chon cach sap xep: ");
        scanf("%d", &option);
        clearInputBuffer();
        
        if (option == 1 || option == 2) break;
        printf("Lua chon khong hop le! Hay nhap lai.\n");
    }
    
    // Bubble sort
    for (int i = 0; i < empCount - 1; i++) {
        for (int j = i + 1; j < empCount; j++) {
            int swap = 0;
            
            if (option == 1 && employees[i].baseSalary > employees[j].baseSalary) {
                swap = 1;
            }
            if (option == 2 && employees[i].baseSalary < employees[j].baseSalary) {
                swap = 1;
            }
            
            if (swap) {
                Employee temp = employees[i];
                employees[i] = employees[j];
                employees[j] = temp;
            }
        }
    }
    
    if (option == 1) {
        printf("Da sap xep tang dan theo luong thanh cong!\n");
    } else {
        printf("Da sap xep giam dan theo luong thanh cong!\n");
    }
}

// F07 - Cham ngay cong
void checkIn() {
    char inpId[20];
    int index;
    
    // Tim nhan vien
    do {
        printf("Nhap ma nhan vien: ");
        fgets(inpId, sizeof(inpId), stdin);
        inpId[strcspn(inpId, "\n")] = '\0';
        
        index = findEmpByID(inpId);
        if (index == -1) {
            printf("Khong tim thay nhan vien co ma %s!\n", inpId);
        }
    } while (index == -1);
    
    // Hien thi thong tin nhan vien
    printf("\nThong tin nhan vien:\n");
    printf("Ma nhan vien: %s\n", employees[index].empId);
    printf("Ten nhan vien: %s\n", employees[index].name);
    printf("Chuc vu: %s\n\n", employees[index].position);
    
    // Nhap ngay cham cong
    int d, m, y;
    do {
        printf("Nhap ngay cham cong (dd/mm/yyyy): ");
        if (scanf("%d/%d/%d", &d, &m, &y) != 3) {
            printf("Nhap sai dinh dang! Nhap lai!\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
    } while (isValidDate(d, m, y) == 0);
    
    // Kiem tra ngay tuong lai
    if (futureDate(d, m, y)) {
        printf("Khong duoc cham cong trong tuong lai!\n");
        return;
    }
    
    // Kiem tra da cham cong chua
    if (checked(inpId, d, m, y) == 1) {
        return;
    }
    
    // Them vao bang cham cong
    genLogID(timeSheet[timeCount].logId);
    strcpy(timeSheet[timeCount].empId, inpId);
    sprintf(timeSheet[timeCount].date, "%02d/%02d/%04d", d, m, y);
    strcpy(timeSheet[timeCount].status, "Di lam");
    timeCount++;
    employees[index].workDay++;
    
    printf("Da cham cong cho nhan vien co ma %s vao ngay %02d/%02d/%04d thanh cong!\n",
           inpId, d, m, y);
}

// F08 - Xem bang cham cong
void viewTimesheet() {
    char inpId[20];
    char buffer[50];
    int sDay, sMonth, sYear;
    int day, month, year;
    
    // Lay ngay hien tai
    time_t t = time(NULL);
    struct tm today = *localtime(&t);
    int cDay = today.tm_mday;
    int cMonth = today.tm_mon + 1;
    int cYear = today.tm_year + 1900;
    
    // Nhap ID nhan vien
    do {
        printf("Nhap ID nhan vien muon xem cham cong: ");
        fgets(inpId, sizeof(inpId), stdin);
        inpId[strcspn(inpId, "\n")] = 0;
        
        if (strlen(inpId) == 0) {
            printf("ID khong duoc bo trong! Vui long nhap lai.\n");
        }
    } while (strlen(inpId) == 0);
    
    int empIndex = findEmpByID(inpId);
    if (empIndex == -1) {
        printf("Khong tim thay nhan vien co ID %s!\n", inpId);
        return;
    }
    
    // Nhap ngay bat dau
    while (1) {
        printf("Nhap ngay bat dau (dd/mm/yyyy): ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        
        if (sscanf(buffer, "%d/%d/%d", &sDay, &sMonth, &sYear) != 3) {
            printf("Dinh dang phai dd/mm/yyyy!\n");
            continue;
        }
        if (sYear < 2000) {
            printf("Nam phai >= 2000!\n");
            continue;
        }
        if (sMonth < 1 || sMonth > 12) {
            printf("Thang khong hop le!\n");
            continue;
        }
        if (sDay < 1 || sDay > 31) {
            printf("Ngay khong hop le!\n");
            continue;
        }
        break;
    }
    
    // Kiem tra ngay tuong lai
    if (futureDate(sDay, sMonth, sYear)) {
        printf("Ngay bat dau khong duoc vuot qua hien tai!\n");
        return;
    }
    
    // Tao danh sach tat ca ngay tu start -> hien tai
    struct DateList {
        char dateStr[20];
    } list[2000];
    
    int listCount = 0;
    day = sDay;
    month = sMonth;
    year = sYear;
    
    while (1) {
        sprintf(list[listCount].dateStr, "%02d/%02d/%04d", day, month, year);
        listCount++;
        
        // Neu da den hien tai thi dung
        if (day == cDay && month == cMonth && year == cYear) break;
        
        // Tang ngay
        int maxDay;
        if (month == 2) {
            maxDay = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 29 : 28;
        } else if (month == 4 || month == 6 || month == 9 || month == 11) {
            maxDay = 30;
        } else {
            maxDay = 31;
        }
        
        day++;
        if (day > maxDay) {
            day = 1;
            month++;
            if (month > 12) {
                month = 1;
                year++;
            }
        }
    }
    
    // Phan trang
    int perPage = PER_PAGE_TIMESHEET;
    int totalPage = (listCount + perPage - 1) / perPage;
    int page = 1;
    char cmd[10];
    
    while (1) {
        system("cls");
        printf("\n======= Bang cham cong %s (Trang %d/%d) =======\n", inpId, page, totalPage);
        printf("ID Log     | Ngay        | Trang thai\n");
        printf("----------------------------------------\n");
        
        int start = (page - 1) * perPage;
        int end = start + perPage;
        if (end > listCount) end = listCount;
        
        for (int idx = start; idx < end; idx++) {
            int found = 0;
            for (int i = 0; i < timeCount; i++) {
                if (strcmp(timeSheet[i].empId, inpId) == 0 &&
                    strcmp(timeSheet[i].date, list[idx].dateStr) == 0) {
                    printf("%-10s | %-12s | %s\n",
                           timeSheet[i].logId,
                           timeSheet[i].date,
                           timeSheet[i].status);
                    found = 1;
                    break;
                }
            }
            if (!found) {
                printf("---------- | %-12s | Nghi lam\n", list[idx].dateStr);
            }
        }
        
        printf("----------------------------------------\n");
        printf("[N]ext [P]revious [G]o to page [Q]uit\n");
        printf("Chon: ");
        fgets(cmd, sizeof(cmd), stdin);
        cmd[strcspn(cmd, "\n")] = 0;
        
        if (strcasecmp_custom(cmd, "N") == 0) {
            if (page < totalPage) page++;
        } else if (strcasecmp_custom(cmd, "P") == 0) {
            if (page > 1) page--;
        } else if (strcasecmp_custom(cmd, "G") == 0) {
            printf("Nhap trang muon den (1 - %d): ", totalPage);
            fgets(cmd, sizeof(cmd), stdin);
            int newPage = atoi(cmd);
            if (newPage >= 1 && newPage <= totalPage) page = newPage;
        } else if (strcasecmp_custom(cmd, "Q") == 0) {
            return;
        }
    }
}

// ==================== HELPER FUNCTIONS ====================
void addSampleList() {
    Employee e1 = {"HG001", "Tran Minh Duc", "Quan li", 2000, 5};
    Employee e2 = {"HG002", "Phung Duy Dat", "Nhan vien", 1000, 3};
    Employee e3 = {"HG003", "Nguyen Minh Hieu", "Giam doc", 5000, 8};
    Employee e4 = {"HG004", "Tang Hieu Thanh", "Chu tich", 10000, 11};
    
    employees[empCount++] = e1;
    employees[empCount++] = e2;
    employees[empCount++] = e3;
    employees[empCount++] = e4;
}
