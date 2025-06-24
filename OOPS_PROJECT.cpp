
#include <bits/stdc++.h>
using namespace std;
#define MAX_EVENTS 100

struct User
{
    string name;
    string address;
    string id;
    string phone;
    string date;
    float payment_advance;
    int booking_id;
};

struct Event
{
    int time_minutes;
    int guest_count;
    int EventNumber;
    bool isBooked;
    string venue;
    User usr;

    // add a new event template
    static Event createEvent(int evNum)
    {
        Event evt;
        evt.EventNumber = evNum;
        cout << "\n    Total Guests: ";
        cin >> evt.guest_count;
        cout << "\n    Total Time (in minutes): ";
        cin >> evt.time_minutes;
        cout << "\n    Venue Name: ";
        cin >> ws;
        getline(cin, evt.venue);
        evt.isBooked = false;
        cout << "\n    Event Added Successfully!\n";
        return evt;
    }

    static void displayEventInfo(const Event &e)
    {
        cout << "\n   Event Number: " << e.EventNumber;
        cout << "\n   Total Guests: " << e.guest_count;
        cout << "\n   Total Time: " << e.time_minutes;
        cout << "\n   Venue: " << e.venue << "\n";
    }
};

Event Events[MAX_EVENTS];
int eventCount = 0;

void manageEvents()
{
    int choice;
    do
    {
        cout << "\n1) Add Event\n2) Search Event\n3) Back to Main Menu\nChoose: ";
        cin >> choice;
        if (choice == 1)
        {
            int evNum;
            cout << "Enter Event Number: ";
            cin >> evNum;
            bool exists = false;
            for (int i = 0; i < eventCount; i++)
            {
                if (Events[i].EventNumber == evNum)
                {
                    exists = true;
                    break;
                }
            }
            if (exists)
            {
                cout << "Event number already exists.\n";
            }
            else if (eventCount < MAX_EVENTS)
            {
                Events[eventCount++] = Event::createEvent(evNum);
            }
            else
            {
                cout << "Event list full!\n";
            }
        }
        else if (choice == 2)
        {
            int evNum;
            cout << "Enter Event number: ";
            cin >> evNum;
            bool found = false;
            for (int i = 0; i < eventCount; i++)
            {
                if (Events[i].EventNumber == evNum)
                {
                    found = true;
                    cout << "\n--------Event Details--------\n";
                    cout << (Events[i].isBooked ? "Booked" : "Available");
                    Event::displayEventInfo(Events[i]);
                    break;
                }
            }
            if (!found)
                cout << "Event not found.\n";
        }
    } while (choice != 3);
}

void bookEvent()
{
    if (eventCount == 0)
    {
        cout << "No events available. Add events first.\n";
        return;
    }
    int evNum;
    cout << "Enter Event Number to book: ";
    cin >> evNum;
    for (int i = 0; i < eventCount; i++)
    {
        if (Events[i].EventNumber == evNum)
        {
            if (Events[i].isBooked)
            {
                cout << "Already booked.\n";
                return;
            }
            Events[i].isBooked = true;
            cout << "Enter Booking ID: ";
            cin >> Events[i].usr.booking_id;
            cout << "Enter Name: ";
            cin >> ws;
            getline(cin, Events[i].usr.name);
            cout << "Enter Address: ";
            getline(cin, Events[i].usr.address);
            cout << "Enter Phone: ";
            cin >> Events[i].usr.phone;
            cout << "Enter Date: ";
            cin >> ws;
            getline(cin, Events[i].usr.date);
            cout << "Enter Advance Payment: ";
            cin >> Events[i].usr.payment_advance;
            cout << "Booking successful.\n";
            return;
        }
    }
    cout << "Event not found.\n";
}

void listAvailableEvents()
{
    bool any = false;
    for (int i = 0; i < eventCount; i++)
    {
        if (!Events[i].isBooked)
        {
            Event::displayEventInfo(Events[i]);
            any = true;
        }
    }
    if (!any)
        cout << "No available events.\n";
}

void searchUser(const string &name)
{
    bool found = false;
    for (int i = 0; i < eventCount; i++)
    {
        if (Events[i].isBooked && Events[i].usr.name == name)
        {
            found = true;
            cout << "\nUser: " << Events[i].usr.name
                 << " | Event#: " << Events[i].EventNumber << "\n";
        }
    }
    if (!found)
        cout << "No bookings found for user.\n";
}

void checkoutEvent()
{
    int evNum;
    cout << "Enter Event Number to checkout: ";
    cin >> evNum;
    for (int i = 0; i < eventCount; i++)
    {
        if (Events[i].EventNumber == evNum && Events[i].isBooked)
        {
            int guests = Events[i].usr.payment_advance; // just placeholder
            // ... cost computations ...
            Events[i].isBooked = false;
            cout << "Checkout completed.\n";
            return;
        }
    }
    cout << "Booking not found.\n";
}

int main()
{
    int choice;
    do
    {
        cout << "\n=== EVENT MANAGEMENT SYSTEM ===\n"
             << "1) Manage Events\n"
             << "2) Book Event\n"
             << "3) List Available Events\n"
             << "4) Search User\n"
             << "5) Checkout Event\n"
             << "6) Exit\nChoose: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            manageEvents();
            break;
        case 2:
            bookEvent();
            break;
        case 3:
            listAvailableEvents();
            break;
        case 4:
        {
            string uname;
            cout << "Enter user name: ";
            cin >> ws;
            getline(cin, uname);
            searchUser(uname);
            break;
        }
        case 5:
            checkoutEvent();
            break;
        case 6:
            cout << "Thank you!\n";
            break;
        default:
            cout << "Invalid choice.\n";
            break;
        }
    } while (choice != 6);
    return 0;
}
