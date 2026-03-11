# Student Management System in C

A console-based **Student Management System** written in C. This system allows users to:

- Add a new student
- Show all students
- Search for a student by ID
- Edit student information
- Delete a student
- Delete all students
- View user guidelines
- About the system

It also manages student courses and ensures unique IDs, emails, and phone numbers.

---

## **Features**

1. **Add Student**
   - Enter ID, Name, Email, Phone, and number of courses
   - Validate for uniqueness and input length
2. **Search Student**
   - Search by student ID
   - Displays student information and their courses
3. **Edit Student**
   - Update Name, Email, Phone, or courses
4. **Delete Student**
   - Remove a single student or all students
5. **User Guidelines**
   - Explains constraints like max courses per student
6. **Dark & Light console support**
   - (If extended with colors)

---

## **Technical Details**

- Language: C
- Platform: Console / Windows (uses `<windows.h>` for delays & screen clear)
- Data Structures: Arrays, Structs
- Files: Currently uses in-memory arrays, no file persistence
- Maximum supported: 100 students, 500 courses

---

## AUTHOR
Khushpreet Kaur
