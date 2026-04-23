## Addressbook-Management-in-C
The **Address Book Management System in C** is a console-based application designed to store, manage, and organize contact information efficiently. This project allows users to perform essential operations such as adding new contacts, searching existing contacts, editing details, deleting entries, and displaying all saved contacts.
---

## 🚀 Features

* Create a new contact
* Search for a contact
* Edit existing contact details
* List all contacts
* Delete a contact
* Save contacts and Exit safely
---

## 📸 Sample Menu

```
1. Create Contact
2. Search Contact
3. Edit Contact
4. List Contacts
5. Delete Contact
6. Save and Exit

```

## 🗂️ Project Structure

```
AddressBook-Management-System/
│
├── main.c           # Entry point of the application
├── contact.c        # Contact-related operations
├── contact.h        # Contact structure & declarations
├── validate.c       # Input validation logic(name, phone, email)
├── validate.h       # Validation function declarations
├── file.c           # File handling operations
│── file.h           # File function declarations
├── ui.h             # Menu and UI-related declarations
├── contacts.txt     # Data storage file (runtime)
└── README.md
```

---
## ⚙️ How It Works

```
* Program starts and loads contacts from file.
* Displays menu options to the user.
* User selects an operation: Create / Search / Edit / Delete / List
* Data is updated in memory.
* On exit, data is saved back to file.
```

---
### Compile

```wsl
gcc *.c
```

### Run

```wsl
./a.out
```

---
## 🧠 Concepts Used

* Conditional statements
* Loops
* Functions 
* Pointers
* Strings
* Structures
* File handling (`fopen`, `fread`, `fwrite`, `fprintf`, `fscanf`)

---

## 📚 Learning Outcomes

* Ability to build a **real-world application using C**
* Strong understanding of **data persistence using files**
* Enhanced **logical thinking and problem-solving skills**
* Hands-on experience with **user input handling and validation**
---

## 👤 Author

**Mohammad Mohseen**

---
