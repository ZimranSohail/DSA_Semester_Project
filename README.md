# Hospital Management System (C++)

## Overview
This project is a **console-based Hospital Management System** developed in **C++** as part of a **previous semester academic project**.

The system demonstrates core programming concepts such as:
- Object-Oriented Programming (OOP)
- Linked Lists & Queues
- Priority-based scheduling
- Basic file handling
- Console-based menu-driven applications

The project manages **patients**, **doctors**, and **hospital workflow** such as admissions, waitlists, doctor assignment, and data persistence.

---

## Features

### Patient Management
- Add patients with:
  - Priority level (1 = highest, 10 = lowest)
  - Disease, ward, room number, CNIC, and admission time
- Priority-based patient queue
- Automatic doctor assignment based on specialization and availability
- Waiting list when doctors are unavailable
- Discharge patients (treated or expired)
- Update patient information

### Doctor Management
- Add and remove doctors
- Track doctor availability
- Assign maximum patient limits per doctor
- Update doctor details
- Save removed doctors to a separate file

### Hospital Workflow
- Automatic reassignment of doctors to waiting patients
- Real-time status updates
- Menu-driven user interface

---

## Data Structures Used
- **Linked Lists** (Doctors & Patients)
- **Queues** (Patient queue, Waiting list)
- **Priority Queue logic** (Patient urgency handling)

---

## File Handling
The system uses basic file handling to store data in text files:

| File Name | Purpose |
|---------|--------|
| `patients.txt` | Stores admitted patient records |
| `doctors.txt` | Stores doctor information |
| `treated_patients.txt` | Stores discharged patient records |
| `removed_doctors.txt` | Stores removed doctor details |

---

## Known Limitations
This project was developed for **learning purposes**, and the following limitations are acknowledged:

- Entire codebase is implemented in **a single `.cpp` file**
- File handling logic may contain inconsistencies
- Limited input validation
- Console-based UI (no GUI)
- Not optimized for real-world hospital systems

These issues were intentionally left unchanged to preserve the **original academic submission**.

---

## Technologies Used
- **Language:** C++
- **Concepts:** OOP, Linked Lists, Queues, File Handling
- **Libraries:** `<iostream>`, `<fstream>`, `<string>`, `<sstream>`, `<ctime>`

---

## How to Run

1. Compile the program:
   ```bash
   g++ hospital.cpp -o hospital
