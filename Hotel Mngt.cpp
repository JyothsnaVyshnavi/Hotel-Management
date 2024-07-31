#include <iostream>
#include <cstring>
using namespace std;

class Customer {
public:
    char name[100];
    char address[100];
    char phone[12];
    float payment_adv;
    int booking_id;
};

class Room {
public:
    char type;
    char stype;
    char ac;
    int room_num;
    int rent;
    int status;
    Customer cust;

    Room addRoom(int);
    void searchRoom(int);
    void displayRoom(Room);
};

Room rooms[100];
int count = 0;

Room Room::addRoom(int rno) {
    Room room;
    room.room_num = rno;
    cout << "\nType Ac/Non-Ac(A/N): ";
    cin >> room.ac;
    cout << "\nType Comfort(N/P): ";
    cin >> room.type;
    cout << "\nSize Single/Double(S/D): ";
    cin >> room.stype;
    cout << "\nDaily Rent: ";
    cin >> room.rent;
    room.status = 0;
    cout << "\nRoom Added Successfully";
    return room;
}

void Room::searchRoom(int rno) {
    int i, found = 0;
    for (i = 0; i < count; i++) {
        if (rooms[i].room_num == rno) {
            found = 1;
            break;
        }
    }
    if (found == 1) {
        cout << "Room Details\n";
        if (rooms[i].status == 1) {
            cout << "\nRoom is Reserved";
        } else {
            cout << "\nRoom is Available";
        }
        displayRoom(rooms[i]);
    } else {
        cout << "Room not found";
    }
}

void Room::displayRoom(Room tempRoom) {
    cout << "\nRoom Number: \t" << tempRoom.room_num;
    cout << "\nAc/Non-Ac: \t" << tempRoom.ac;
    cout << "\nComfort: \t" << tempRoom.type;
    cout << "\nSize: \t" << tempRoom.stype;
    cout << "\nRent: \t" << tempRoom.rent;
}

class HotelMgnt : protected Room {
public:
    void checkIn();
    void getAvailRoom();
    void searchCustomer(char *);
    void checkOut(int);
    void guestSummaryReport();
};

void HotelMgnt::guestSummaryReport() {
    if (count == 0)
        cout << "\nNo Guest in Hotel !";
    for (int i = 0; i < count; i++) {
        if (rooms[i].status == 1) {
            cout << "\nCustomer Name: " << rooms[i].cust.name;
            cout << "\nRoom Number: " << rooms[i].room_num;
            cout << "\nAddress: " << rooms[i].cust.address;
            cout << "\nPhone Number: " << rooms[i].cust.phone;
            cout << "\n--------------------------------------";
        }
    }
}

void HotelMgnt::checkIn() {
    int i, found = 0, rno;
    cout << "\nEnter Room Number: ";
    cin >> rno;
    for (i = 0; i < count; i++) {
        if (rooms[i].room_num == rno) {
            found = 1;
            break;
        }
    }
    if (found == 1) {
        if (rooms[i].status == 1) {
            cout << "\nRoom is already booked";
            return;
        }
        cout << "\nEnter Booking id: ";
        cin >> rooms[i].cust.booking_id;
        cout << "\nEnter customer name: ";
        cin >> rooms[i].cust.name;
        cout << "\nEnter Phone Number: ";
        cin >> rooms[i].cust.phone;
        cout << "\nEnter advance payment ";
        cin >> rooms[i].cust.payment_adv;
        rooms[i].status = 1;
        cout << "\nCustomer Checked in successfully";
    }
}

void HotelMgnt::getAvailRoom() {
    int i, found = 0;
    for (i = 0; i < count; i++) {
        if (rooms[i].status == 0) {
            displayRoom(rooms[i]);
            cout << "\n\nPress enter for next room";
            found = 1;
        }
    }
    if (found == 0) {
        cout << "\nAll rooms are reserved";
    }
}

void HotelMgnt::searchCustomer(char *pname) {
    int i, found = 0;
    for (i = 0; i < count; i++) {
        if (rooms[i].status == 1 && strcmp(rooms[i].cust.name, pname) == 0) {
            cout << "\nCustomer Name: " << rooms[i].cust.name;
            cout << "\nRoom Number: " << rooms[i].room_num;
            cout << "\n\nPress Enter for next record";
            found = 1;
        }
    }
    if (found == 0) {
        cout << "\nPerson Not found";
    }
}

void HotelMgnt::checkOut(int roomnum) {
    int i, found = 0, days;
    float billAmount = 0;
    for (i = 0; i < count; i++) {
        if (rooms[i].room_num == roomnum && rooms[i].status == 1) {
            found = 1;
            break;
        }
    }
    if (found == 1) {
        cout << "\nEnter number of days: ";
        cin >> days;
        billAmount = days * rooms[i].rent;
        cout << "\nPayable Amount left: " << (billAmount - rooms[i].cust.payment_adv);
        cout << "\nChecked out successfully";
        rooms[i].status = 0;
    }
}

void manageRooms() {
    Room room;
    int opt, rno, i, flag = 0;
    do {
        cout << "\n___Manage Rooms___";
        cout << "\n1.Add room";
        cout << "\n2.Search Room";
        cout << "\n3.Back to Main Menu";
        cout << "\n\nEnter Option: ";
        cin >> opt;
        switch (opt) {
            case 1:
                cout << "\nEnter Room Number: ";
                cin >> rno;
                for (i = 0; i < count; i++) {
                    if (rooms[i].room_num == rno) {
                        flag = 1;
                    }
                }
                if (flag == 1) {
                    cout << "\nRoom Number is present\nPlease enter unique room";
                    flag = 0;
                } else {
                    rooms[count] = room.addRoom(rno);
                    count++;
                }
                break;
            case 2:
                cout << "\nEnter room number: ";
                cin >> rno;
                room.searchRoom(rno);
                break;
            case 3:
                break;
            default:
                cout << "\nPlease select above options only";
                break;
        }
    } while (opt != 3);
}

int main() {
    HotelMgnt hm;
    int opt, rno;
    char pname[100];
    do {
        cout << "\n###Hotel Management###";
        cout << "\n1.Manage Room";
        cout << "\n2.Check-In Room";
        cout << "\n3.Available Room";
        cout << "\n4.Search Customer";
        cout << "\n5.Checkout Room";
        cout << "\n6.Guest Summary";
        cout << "\n7.Quit";
        cout << "\n\nEnter option: ";
        cin >> opt;
        switch (opt) {
            case 1:
                manageRooms();
                break;
            case 2:
                if (count == 0) {
                    cout << "\nNo rooms are registered, please add room first";
                } else {
                    hm.checkIn();
                }
                break;
            case 3:
                if (count == 0) {
                    cout << "\nNo rooms are registered, please add room first";
                } else {
                    hm.getAvailRoom();
                }
                break;
            case 4:
                if (count == 0) {
                    cout << "\nNo rooms are registered, please add room first";
                } else {
                    cout << "Enter Customer Name: ";
                    cin >> pname;
                    hm.searchCustomer(pname);
                }
                break;
            case 5:
                if (count == 0) {
                    cout << "\nNo rooms are registered, please add room first";
                } else {
                    cout << "Enter Room Number: ";
                    cin >> rno;
                    hm.checkOut(rno);
                }
                break;
            case 6:
                hm.guestSummaryReport();
                break;
            case 7:
                cout << "\nThank you for using our App";
                break;
            default:
                cout << "\nSelect valid option";
                break;
        }
    } while (opt != 7);

    return 0;
}
