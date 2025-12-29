#include <iostream>
#include <algorithm>
#include <cctype>
#include<fstream>
#include<string>
#include<sstream>
#include<ctime>
#include <chrono>
using namespace std;
 string get_current_time() {
    time_t timestamp;
    char timeBuffer[26];
    time(&timestamp);
    ctime_s(timeBuffer, sizeof(timeBuffer), &timestamp);
    string current_time(timeBuffer);
    return current_time;
}

struct Patient {
    string admit_time;
    string name;
    int age;
    string gender;
    int id;
    string cnic;
    string disease;
    string ward;
    string assigned_doctor;
    int room_num;
    int priority_level;
    string status;
    Patient* Next;

};
struct Doctor {
    int ID;
    string name;
    string specialization;
    string phone_number;;
    bool Availlability;
    int numpatient;
    int max_patients;
    Doctor* next;
};
class Doctor_Queue {

    Doctor* rear;
public:
    Doctor* front;
    Doctor_Queue() {
        front = NULL;
        rear = NULL;
    }

    Doctor* create(int ID,
        string name,
        string specialization,
        string phone_number,
        bool Availlability,
        int numpatient,
        int Max_patients) {
        Doctor* newdoctor = new Doctor();
        newdoctor->ID = ID;
        newdoctor->name = name;
        newdoctor->specialization = specialization;
        newdoctor->phone_number = phone_number;
        newdoctor->Availlability = Availlability;
        newdoctor->numpatient = numpatient;
        newdoctor->max_patients = Max_patients;
        newdoctor->next = NULL;
        return newdoctor;
    }

    void adddoc(int ID,
        string name,
        string specialization,
        string phone_number,
        bool Availlability,
        int Max
    ) {
        Doctor* newdoc = create(ID, name, specialization, phone_number, Availlability, 0, Max);
        if (front == NULL && rear == NULL) {
            front = newdoc;
            rear = newdoc;
            cout << "Doctor Added successfully";
            return;
        }
        rear->next = newdoc;
        rear = newdoc;
        cout << "Doctor Added successfully";
    }

    void remove(int id) {
        if (front == NULL && rear == NULL) {
            cout << "The doctor's list is empty at the moment." << endl;
            return;
        }

        Doctor* temp = front;
        Doctor* prev = NULL;

        while (temp != NULL && temp->ID != id) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL) {
            cout << "Doctor with ID: " << id << " not found." << endl;
            return;
        }
        save_removed_doctor_to_file(temp);
        if (temp == front) {
            front = front->next;
        }
        else {
            prev->next = temp->next;
        }

        if (temp == rear) {
            rear = prev;
        }
        delete temp;
        cout << "Doctor with ID: " << id << " removed successfully." << endl;
    }

    void save_removed_doctor_to_file(Doctor* doctor) {
        ofstream file("removed_doctors.txt", ios::app);  // Append mode
        if (!file) {
            cout << "Error opening file for saving removed doctor!" << endl;
            return;
        }
        string availability = doctor->Availlability ? "YES" : "NO";
        file << doctor->ID << ","
            << doctor->name << ","
            << doctor->specialization << ","
            << doctor->numpatient << ","
            << doctor->phone_number << ","
            << availability << endl;
        file.close();
        cout << "Removed doctor data saved successfully!" << endl;
    }

    Doctor* searchbyspecialization(string spec) {
        Doctor* temp = front;

        while (temp != NULL) {
            if (temp->specialization == spec) {
                return temp;
            }
            temp = temp->next;
        }
        cout << "Doctor with ID " << spec << " not found" << endl;
        return NULL;
    }
    void update_availability(Doctor* doc) {
        if (doc->numpatient < 5) {
            doc->Availlability = true;
            cout << "Dr." << doc->name << " is Available now." << endl;
        }
    }


    Doctor* searchbyid(int id) {
        Doctor* temp = front;
        while (temp != NULL) {
            if (temp->ID == id) {
                return temp;
            }
            temp = temp->next;
        }
        cout << "Doctor with ID " << id << " not found" << endl;
        return NULL;
    }
    void Display_Doctors() {
        Doctor* temp = front;
        while (temp != NULL) {
            cout << "Name: " << temp->name << endl;
            cout << "ID:" << temp->ID << endl;
            cout << "Specialization " << temp->specialization << endl;
            cout << "Contact: " << temp->phone_number << endl;
            if (temp->Availlability == true) {
                cout << "Available" << endl;
            }
            else {
                cout << "Not Available" << endl;
            }
            cout << "Total number of patients " << temp->numpatient << endl;
            temp = temp->next;
        }
    }

    void save_doctors_to_file(Doctor* head) {
        ofstream file("doctors.txt");
        if (!file) {
            cout << "Error opening file for saving!" << endl;
            return;
        }
        Doctor* current = head;
        while (current != nullptr) {
            string availability;
            if (current->Availlability == true) {
                availability = "YES";
            }
            else {
                availability = "NO";
            }

            file << current->ID << ","
                << current->name << ","
                << current->specialization << ","
                << current->numpatient << ","
                << current->phone_number << ","
                << availability << endl;
            current = current->next;
        }
        file.close();
        cout << "Doctor data saved successfully!" << endl;
    }

    void load_doctors_from_file(Doctor*& head) {
        ifstream file("doctors.txt");
        if (!file) {
            cout << "Error opening file for loading!" << endl;
            return;
        }
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string id_str, name, specialization, numpatients_str, phone_number, availability_str;
            getline(ss, id_str, ',');
            getline(ss, name, ',');
            getline(ss, specialization, ',');
            getline(ss, numpatients_str, ',');
            getline(ss, phone_number, ',');
            getline(ss, availability_str, ',');

            Doctor* new_doctor = new Doctor;
            new_doctor->ID = stoi(id_str);
            new_doctor->name = name;
            new_doctor->specialization = specialization;
            new_doctor->phone_number = phone_number;
            new_doctor->numpatient = stoi(numpatients_str);
            new_doctor->Availlability = (availability_str == "YES");
            new_doctor->next = nullptr;

            if (head == nullptr) {
                head = new_doctor;
            }
            else {
                Doctor* temp = head;
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = new_doctor;
            }
        }
        file.close();
        cout << "Doctor data loaded successfully!" << endl;
    }

};

class Patient_Queue {

    
public:
    Patient* rear;
    Patient* front;
    Patient* waitlist;

    Patient* create(string N, int age, string gender, int ID, string CNIC, string DISEASE, const string& WARD, string AD, int RN, int PL, string time)
    {
        Patient* new_Patient = new Patient();

        new_Patient->name = N;
        new_Patient->age = age;
        new_Patient->gender = gender;
        new_Patient->id = ID;
        new_Patient->cnic = CNIC;
        new_Patient->disease = DISEASE;
        new_Patient->ward = WARD;
        new_Patient->assigned_doctor = AD;
        new_Patient->room_num = RN;
        new_Patient->priority_level = PL;
        new_Patient->status = "To be declared";
        new_Patient->admit_time = time;
        new_Patient->Next = nullptr;
        return new_Patient;
    }

    void add_patient(string N, int age, string gender, int ID, string CNIC, string DISEASE, string WARD, string AD, int RN, int PL, string time) {
        Patient* new_patient = create(N, age, gender, ID, CNIC, DISEASE, WARD, AD, RN, PL, time);

        if (front == nullptr) {
            front = rear = new_patient;
            return;
        }
        // Priority 1 = highest and Priority 10 = loweest
        if (PL < front->priority_level) {
            new_patient->Next = front;
            front = new_patient;
            return;
        }
        Patient* current = front;
        while (current->Next != nullptr && PL >= current->Next->priority_level) {
            current = current->Next;
        }

        new_patient->Next = current->Next;
        current->Next = new_patient;
        if (current->Next == nullptr) {
            rear = new_patient;
        }
        cout << "Patient " << N << " added to queue." << endl;

    };

    void add_to_waitlist(Patient* patient) {
        patient->Next = nullptr;
        if (waitlist == nullptr) {
            waitlist = patient;
        }
        else {
            Patient* temp = waitlist;
            while (temp->Next != nullptr) {
                temp = temp->Next;
            }
            temp->Next = patient;
        }
        cout << "Patient" << patient->name << " Added to wailist";
    }

    Patient* get_next_waiting_list() {
        if (waitlist == nullptr) {
            cout << "The Wait list is empty" << endl;
            return  nullptr;
        }
        Patient* first = waitlist;
        waitlist = waitlist->Next;
        return first;
    }

    void assign_doctor_to_waiting(Doctor_Queue& doc_queue) {
        if (waitlist == nullptr) {
            cout << "The waitlist is empty." << endl;
            return;
        }

        Doctor* available_doctor = nullptr;
        Doctor* temp_doc = doc_queue.front;

        // Check for an available doctor
        while (temp_doc != nullptr) {
            if (temp_doc->Availlability && temp_doc->numpatient < 5) {
                available_doctor = temp_doc;
                break;
            }
            temp_doc = temp_doc->next;
        }

        if (available_doctor == nullptr) {
            // No doctors are available, no need to fetch the patient
            cout << "No doctors are currently available to assign patients from the waitlist." << endl;
            return;
        }

        // Fetch the next patient from the waitlist
        Patient* patient = get_next_waiting_list();

        // Assign the doctor to the patient
        patient->assigned_doctor = available_doctor->name;
        patient->status = "Treatment Ongoing";
        available_doctor->numpatient++;

        if (available_doctor->numpatient == 5) {
            available_doctor->Availlability = false;
        }

        cout << "Patient " << patient->name << " assigned to Dr. " << available_doctor->name << endl;
    }

    Patient* remove_patient() {
        // priortiy level 0 is treatment successful and -1 is unsuccessful/ patient expired
        if (front->priority_level == 0 || front->priority_level == -1) {
            int status = front->priority_level;
            if (status == 0) {
                cout << "Treatment Successful" << endl;
            }
            if (status == -1) {
                cout << "Treatment Unsuccessful. Patient Expired." << endl;
            }
            Patient* temp = front;
            front = front->Next;
            return temp;

        }
    };
    void display() {
        Patient* temp = front;

        if (temp == nullptr) {
            cout << "No Patients in the Queue" << endl;
            return;
        }
        while (temp != nullptr) {
            cout << "---------------------------Patient Datails--------------------------------------------" << endl;
            cout << "Name: " << temp->name;
            cout << "Age: " << temp->age;
            cout << "Gender: " << temp->gender;
            cout << "ID: " << temp->id;
            cout << "CNIC: " << temp->cnic;
            cout << "Disease:  " << temp->disease;
            cout << "Ward: " << temp->ward;
            cout << "Attending Doctor: " << temp->assigned_doctor;
            cout << "Priority(1-10)" << temp->priority_level;
            cout << "Admit Time: " << temp->admit_time;
            temp = temp->Next;
        }
    }

    void save_patients_to_file(Patient* front) {
        ofstream file("patients.txt");
        if (!file) {
            cout << "Error opening file for saving!" << endl;
            return;
        }
        Patient* current = front;
        while (current != nullptr) {
            file << current->id << ","
                << current->name << ","
                << current->age << ","
                << current->gender << ","
                << current->cnic << ","
                << current->disease << ","
                << current->ward << ","
                << current->assigned_doctor << ","
                << current->room_num << ","
                << current->priority_level << ","
                << current->admit_time << ","
                << current->status << endl;
            current = current->Next;
        }
        file.close();
        cout << "Patient data saved successfully!" << endl;
    }
    void Add_Patient(Patient*& front, Patient*& rear, Patient* new_patient) {
        if (front == nullptr) {
            // If the queue is empty, set front and rear to the new patient
            front = rear = new_patient;
        }
        else {
            // Append the new patient to the end of the queue
            rear->Next = new_patient;
            rear = new_patient;
        }
        new_patient->Next = nullptr; // Ensure the new rear's Next is null
    }

    void load_patients_from_file(Patient*& front, Patient*& rear) {
        ifstream file("patients.txt");
        if (!file.is_open()) {
            cout << "Error opening file for loading!" << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string id_str, name, gender, cnic, disease, ward, doctor, room_num_str, priority_str, status, age_str, admit_time;
            int id = 0, room_num = 0, priority = 0, age = 0;

            // Parse the line from the file
            getline(ss, id_str, ',');         // ID
            getline(ss, name, ',');          // Name
            getline(ss, gender, ',');        // Gender
            getline(ss, cnic, ',');          // CNIC
            getline(ss, disease, ',');       // Disease
            getline(ss, ward, ',');          // Ward
            getline(ss, doctor, ',');        // Assigned Doctor
            getline(ss, room_num_str, ',');  // Room Number
            getline(ss, priority_str, ',');  // Priority Level
            getline(ss, status, ',');        // Status
            getline(ss, age_str, ',');       // Age
            getline(ss, admit_time, ',');    // Admit Time

            try {
                // Convert strings to integers
                id = stoi(id_str);
                room_num = stoi(room_num_str);
                priority = stoi(priority_str);
                age = stoi(age_str);
            }
            catch (const exception& e) {
                cout << "Error parsing line: " << line << " - " << e.what() << endl;
                continue;  // Skip invalid data
            }

            // Create a new Patient object
            Patient* new_patient = new Patient;
            new_patient->id = id;
            new_patient->name = name;
            new_patient->gender = gender;
            new_patient->cnic = cnic;
            new_patient->disease = disease;
            new_patient->ward = ward;
            new_patient->assigned_doctor = doctor;
            new_patient->room_num = room_num;
            new_patient->priority_level = priority;
            new_patient->status = status;
            new_patient->age = age;
            new_patient->admit_time = admit_time;
            new_patient->Next = nullptr;

            Add_Patient(front, rear, new_patient);
            // Add the patient to the queue while maintaining priority
           /* if (front == nullptr) {
                // Queue is empty, initialize it
                front = rear = new_patient;
            }
                // Higher priority than the current front
            else if (priority < front->priority_level) {
                new_patient->Next = front;
                front = new_patient;
                cout << "Inserted patient at the front of the queue." << endl;
            }

            else {
                // Traverse the queue to find the correct position
                Patient* temp = front;
                while (temp->Next != nullptr && temp->Next->priority_level <= priority) {
                    temp = temp->Next;
                }
                new_patient->Next = temp->Next;
                temp->Next = new_patient;

                // Update rear if the new patient is added at the end
                if (new_patient->Next == nullptr) {
                    rear = new_patient;
                }
            }*/
            cout << "Loaded patient: " << name << " (ID: " << id << ", Priority: " << priority << ")" << endl;
        }

        file.close();
        cout << "Patient data loaded successfully!" << endl;
    }
    

};
class Hospital : private Patient_Queue, Doctor_Queue {
    Patient_Queue pq;
    Doctor_Queue dq;
public:
    void addpatient(string N, int age, string gender,
        int ID, string CNIC,
        string DISEASE, string WARD,
        int RN, int PL) {
        string time = get_current_time();

        pq.add_patient(N, age, gender, ID, CNIC, DISEASE, WARD, "Not Assigned", RN, PL, time);

        // assigning doctor
        Patient* patient_front = pq.front;
        Doctor* doctor_temp = dq.front;
        bool doctor_assigned = false;

        while (doctor_temp != nullptr) {
            if (WARD == doctor_temp->specialization
                &&
                doctor_temp->Availlability == true && doctor_temp->numpatient < doctor_temp->max_patients) {
                patient_front->assigned_doctor = doctor_temp->name;
                doctor_temp->numpatient++;
                cout << "Dr." << doctor_temp->name << " Assigned to patient" << patient_front->name;
                patient_front->status = "Treatment Ongoing";

                if (doctor_temp->numpatient == doctor_temp->max_patients) {
                    doctor_temp->Availlability = false;
                }
                doctor_assigned = true;
                break;
            }
            doctor_temp = doctor_temp->next;
        }
        if (!doctor_assigned) {
            cout << "Doctors not available right now. Please Wait Doctor will be assigned as soon a another becomes available. You have been added to waitlist" << endl;
            patient_front->status = "Waitlisted";
            pq.add_to_waitlist(patient_front);
        }
    }
    void Reassign_doctor_to_waiting() {
        pq.assign_doctor_to_waiting(dq);
    }
    void adddoc() {
        int id, max;
        string n;
        string spec;
        string phone;
        string availabilty;
        bool Availlability = true;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, n);
        cout << endl;
        cout << "Enter ID: ";
        cin >> id;
        cout << endl;
        cout << "Enter Specialization: ";
        cin.ignore();
        cin >> spec;
        cout << endl;
        cout << "Enter Phone Number: ";
        cin >> phone;
        cout << endl;
        cout << "Is doctor available (YES OR NO) : ";
        cin >> availabilty;
        cout << "Enter the maximu number of patient Dr." << n << " can take: ";
        cin >> max;
        cout << endl;
        transform(availabilty.begin(), availabilty.end(), availabilty.begin(), ::toupper);
        if (availabilty == "YES") { Availlability = true; }
        else {
            Availlability = false;
        }

        dq.adddoc(id, n, spec, phone, Availlability, max);
    }

    void dischage_OR_remove() {
        Patient* patient = pq.front;
        while (patient != nullptr) {
            if (patient->priority_level == 0 || patient->priority_level == -1) {
                Patient* to_remove = pq.remove_patient();
                save_treated_patient_to_file(to_remove);
                delete to_remove;
                patient = pq.front;

            }
            else if (patient->priority_level > 1 && patient->priority_level < 11) {
                cout << "The Patient is being Treated. Can''t be removed right now!!!";
                break;
            }
            else {
                cout << "Invalid Priority level entered";
                break;
            }
        }
    }
    void save_treated_patient_to_file(Patient* patient) {
        ofstream file("treated_patients.txt", ios::app);  // Append mode
        if (!file) {
            cout << "Error opening file for saving treated patient!" << endl;
            return;
        }

        // Save patient details in CSV format (or any preferred format)
        file << patient->id << ","
            << patient->name << ","
            << patient->age << ","
            << patient->gender << ","
            << patient->cnic << ","
            << patient->disease << ","
            << patient->ward << ","
            << patient->assigned_doctor << ","
            << patient->room_num << ","
            << patient->priority_level << ","
            << patient->status << endl;
        file.close();
        cout << "Treated patient data saved successfully!" << endl;
    }
    void updateInfoPatient(int ID) {
        Patient* temp = pq.front; // Assuming pq.front points to the start of the queue

        // Traverse the list to find the patient with the given ID
        while (temp != nullptr && temp->id != ID) {
            temp = temp->Next;
        }

        if (temp == nullptr) {
            cout << "Patient with ID " << ID << " not found." << endl;
            return;
        }

        int option;
        cout << "Choose information to update:" << endl;
        cout << "1. ID" << endl;
        cout << "2. Name" << endl;
        cout << "3. Age" << endl;
        cout << "4. CNIC" << endl;
        cout << "5. Status" << endl;
        cout << "6. Ward" << endl;
        cout << "7. Room Number" << endl;
        cin >> option;
        cin.ignore(); // Clear input buffer

        switch (option) {
        case 1: {
            int newID;
            cout << "Enter new ID: ";
            cin >> newID;
            temp->id = newID;
            break;
        }
        case 2: {
            string newName;
            cout << "Enter new Name: ";
            cin.ignore();
            getline(cin, newName);
            temp->name = newName;
            break;
        }
        case 3: {
            int newAge;
            cout << "Enter new Age: ";
            cin >> newAge;
            temp->age = newAge;
            break;
        }
        case 4: {
            int newCNIC;
            cout << "Enter new CNIC: ";
            cin >> newCNIC;
            temp->cnic = newCNIC;
            break;
        }
        case 5: {
            string newStatus;
            cout << "Enter new Status (Admitted/Discharged): ";
            cin.ignore();
            getline(cin, newStatus);
            temp->status = newStatus;
            break;
        }
        case 6: {
            string newWard;
            cout << "Enter new Ward: ";
            cin.ignore();
            getline(cin, newWard);
            temp->ward = newWard;
            break;
        }
        case 7: {
            int newRoomNumber;
            cout << "Enter new Room Number: ";
            cin >> newRoomNumber;
            temp->room_num = newRoomNumber;
            break;
        }
        default:
            cout << "Invalid option selected." << endl;
        }

        cout << "Patient information updated successfully!" << endl;
    }

    void remove_doc(int id) {
        dq.remove(id);

    }
    void Update_doctor_info(int id) {
        Doctor* temp = dq.front; // Assuming pq.front points to the start of the queue

        // Traverse the list to find the patient with the given ID
        while (temp != nullptr && temp->ID != id) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Doctor with ID " << id << " not found." << endl;
            return;
        }
        int option;
        cin >> option;
        cin.ignore(); // Clear input buffer

        switch (option) {
        case 1: {
            int newID;
            cout << "Enter new ID: ";
            cin >> newID;
            temp->ID = newID;
            break;
        }
        case 2: {
            string newName;
            cout << "Enter new Name: ";
            cin.ignore();
            getline(cin, newName);
            temp->name = newName;
            break;
        }
        case 3: {
            int Phone;
            cout << "Enter new Contact: ";
            cin >> Phone;
            temp->phone_number = Phone;
            break;
        }
        case 4: {
            string availbility;
            cout << "Enter Avaialability( YES OR NO): ";
            cin >> availbility;
            if (availbility == "YES") {
                temp->Availlability = true;
            }
            else if (availbility == "NO") {
                temp->Availlability = false;
            }
            break;
        }
        case 5: {
            int max;
            cout << "Enter Maximum no. of patients: ";
            cin.ignore();
            cin >> max;
            temp->max_patients = max;
            break;
        }
        default:
            cout << "Invalid option selected." << endl;
        }

        cout << "Doctor information updated successfully!" << endl;
    }
    void save_all_data() {
        dq.save_doctors_to_file(dq.front);
        pq.save_patients_to_file(pq.front);
    }

    void read_doctors() {
        dq.load_doctors_from_file(dq.front);
        ;
    }
    void read_patients() {
        pq.load_patients_from_file(pq.front, pq.rear);
    }
     
    
        void display_doctors() {
            dq.Display_Doctors();
        }
        void display_patients() {
            pq.display();
        }
};

int main() {
    Hospital hospital;
    int choice;

    string time = get_current_time();
    cout << time;
   // hospital.read_all_data();
   
    do {
        cout << "=========================\n";
        cout << "  Hospital Management System\n";
        cout << "=========================\n";
        cout << "1. Add Patient\n";
        cout << "2. Add Doctor\n";
        cout << "3. Display Patients\n";
        cout << "4. Display Doctors\n";
        cout << "5. Remove Patient(Treated or Expired\n";
        cout << "6. Remove Doctor\n";
        cout << "7. Update Patient Information\n";
        cout << "8. Update Doctor Information\n";
        cout << "9. Reassign Doctor to Waiting Patient\n";
        cout << "10. Save Data\n";
        cout << "11. Load Data\n";
        cout << "12. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string name, gender, disease, ward,cnic;
            int age, id;
            int room_num, priority_level;
            cout << "Enter Patient Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Age: ";
            cin >> age;
            cout << "Enter Gender: ";
            cin >> gender;
            cin.ignore();
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter CNIC: ";
            cin >> cnic;
            cin.ignore();
            cout << "Enter Disease: ";
            getline(cin, disease);
          
            cout << "Enter Ward: ";
            getline(cin, ward);
            cout << "Enter Room Number: ";
            cin >> room_num;
            cout << "Enter Priority Level (1-10): ";
            cin >> priority_level;

            hospital.addpatient(name, age, gender, id, cnic, disease, ward, room_num, priority_level);
            break;
        }
        case 2: {
            hospital.adddoc();
            break;
        }
        case 3:
            hospital.display_patients();
            break;
        case 4:
            hospital.display_doctors();
            break;
        case 5: {
            hospital.dischage_OR_remove();
            break;
        }
        case 6: {
            int id;
            cout << "Enter Doctor ID to Remove: ";
            cin >> id;
            hospital.remove_doc(id);
            break;
        }
        case 7: {
            int id;
            cout << "Enter Patient ID to Update: ";
            cin >> id;
            hospital.updateInfoPatient(id);
            break;
        }
        case 8: {
            int id;
            cout << "Enter Doctor ID to Update: ";
            cin >> id;
            hospital.Update_doctor_info(id);
            break;
        }
        case 9:
            hospital.Reassign_doctor_to_waiting();
            break;
        case 10:
            hospital.save_all_data();
            break;
        case 11:
            hospital.read_doctors();
            hospital.read_patients();
            break;
        case 12:
            cout << "Exiting system. Saving data...\n";
            hospital.save_all_data();
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 12);
    
    return 0;
}