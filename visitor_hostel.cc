#include <iostream>
#include <string>
#include <mysql/mysql.h>

using namespace std;

// Database connection variables
const string DB_HOST = "localhost";
const string DB_USER = "root";
const string DB_PASSWORD = "password";
const string DB_NAME = "visitor_hostel";

// Function to connect to the database
bool connectToDB(MYSQL *conn) {
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST.c_str(), DB_USER.c_str(), DB_PASSWORD.c_str(), DB_NAME.c_str(), 0, NULL, 0)) {
        cout << "Error connecting to database: " << mysql_error(conn) << endl;
        return false;
    }
    return true;
}

// Function to create a new booking
void createBooking(MYSQL *conn, string customerName, int roomNumber, string fromDate, string toDate, float advancePayment) {
    string query = "INSERT INTO bookings (customer_name, room_number, from_date, to_date, advance_payment) VALUES ('" + customerName + "', " + to_string(roomNumber) + ", '" + fromDate + "', '" + toDate + "', " + to_string(advancePayment) + ")";
    if (mysql_query(conn, query.c_str())) {
        cout << "Error creating booking: " << mysql_error(conn) << endl;
    } else {
        cout << "Booking created successfully!" << endl;
    }
}

// Function to search for a customer
void searchCustomer(MYSQL *conn, string customerName) {
    string query = "SELECT * FROM customers WHERE name = '" + customerName + "'";
    MYSQL_RES *result;
    MYSQL_ROW row;
    if (mysql_query(conn, query.c_str())) {
        cout << "Error searching for customer: " << mysql_error(conn) << endl;
    } else {
        result = mysql_store_result(conn);
        while ((row = mysql_fetch_row(result))) {
            cout << "Customer found: " << row[0] << " " << row[1] << endl;
        }
        mysql_free_result(result);
    }
}

// Function to manage rooms
void manageRooms(MYSQL *conn) {
    int option;
    cout << "Manage Rooms" << endl;
    cout << "1. Add Room" << endl;
    cout << "2. Search Room" << endl;
    cout << "3. Back to Main Menu" << endl;
    cin >> option;
    switch (option) {
        case 1: {
            int roomNumber;
            string roomType;
            string comfort;
            string size;
            float dailyRent;
            cout << "Enter room number: ";
            cin >> roomNumber;
            cout << "Enter room type (AC/Non-AC): ";
            cin >> roomType;
            cout << "Enter comfort (S/N): ";
            cin >> comfort;
            cout << "Enter size (B/S): ";
            cin >> size;
            cout << "Enter daily rent: ";
            cin >> dailyRent;
            string query = "INSERT INTO rooms (room_number, room_type, comfort, size, daily_rent) VALUES (" + to_string(roomNumber) + ", '" + roomType + "', '" + comfort + "', '" + size + "', " + to_string(dailyRent) + ")";
            if (mysql_query(conn, query.c_str())) {
                cout << "Error adding room: " << mysql_error(conn) << endl;
            } else {
                cout << "Room added successfully!" << endl;
            }
            break;
        }
        case 2: {
            int roomNumber;
            cout << "Enter room number: ";
            cin >> roomNumber;
            string query = "SELECT * FROM rooms WHERE room_number = " + to_string(roomNumber);
            MYSQL_RES *result;
            MYSQL_ROW row;
            if (mysql_query(conn, query.c_str())) {
                cout << "Error searching for room: " << mysql_error(conn) << endl;
            } else {
                result = mysql_store_result(conn);
                while ((row = mysql_fetch_row(result))) {
                    cout << "Room found: " << row[0] << " " << row[1] << " " << row[2] << " " << row[3] << " " << row[4] << endl;
                }
                mysql_free_result(result);
            }
            break;
        }
        case 3:
            return;
        default:
            cout << "Invalid option" << endl;
    }
}

int main() {
    MYSQL *conn;
    if (!connectToDB(conn)) {
        return 1;
    }

    int option;
    cout << "Hotel Management System" << endl;
    cout << "1. Manage Rooms" << endl;
    cout << "2. Check-In Room" << endl;
    cout << "3. Available Rooms" << endl;