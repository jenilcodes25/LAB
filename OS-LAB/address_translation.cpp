#include <iostream>
using namespace std;

int main() {
    int logical_size, physical_size, page_size, n_pages;
    
    cout << "Enter Logical Address Space size: ";
    cin >> logical_size;
    cout << "Enter Physical Address Space size: ";
    cin >> physical_size;
    cout << "Enter Page size: ";
    cin >> page_size;
    
    n_pages = logical_size / page_size;
    cout << "Number of pages: " << n_pages << endl;

    int page_table[n_pages];
    cout << "Enter Frame Number for each page (Page Table):\n";
    for (int i = 0; i < n_pages; i++) {
        cout << "Page " << i << " -> Frame #: ";
        cin >> page_table[i];
    }

    int logical_address;
    cout << "Enter Logical Address to translate: ";
    cin >> logical_address;

    // Calculate page number and offset
    int page_number = logical_address / page_size;
    int offset = logical_address % page_size;

    if (page_number >= n_pages) {
        cout << "Invalid Logical Address!" << endl;
        return 0;
    }

    int frame_number = page_table[page_number];
    int physical_address = frame_number * page_size + offset;

    cout << "\nLogical Address: " << logical_address << endl;
    cout << "Page Number: " << page_number << ", Offset: " << offset << endl;
    cout << "Frame Number: " << frame_number << endl;
    cout << "Physical Address: " << physical_address << endl;

    return 0;
}
