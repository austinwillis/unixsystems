// File: dbmwrite.cpp
// Example program illustrating gdbm database routines to write a db
// This example uses two different record sizes.

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <gdbm.h>
#include <iostream>
#include <cstring>
#include "employee.h"

using namespace std;

int main()
{
   GDBM_FILE dbf;

   // datum contains 'char *dptr' and 'int dsize' members (see gdbm info)
   datum key, content, datain;

   // structs from employee.h
   struct keystr keydata;
   struct salrec salary;
   struct emprec employee;

   // Use the employee id and record type as the key
   key.dptr = (char *)(&keydata);
   key.dsize = sizeof(keydata);

   // g++ warning happens here because first parameter is not declared const
   // open/create data base file for writing
   dbf = gdbm_open("datafile.dat", 0, GDBM_WRCREAT, 0644, 0);

   // Fill employee struct
   employee.id = 0;
   strcpy(employee.lname,"Flintstone");
   strcpy(employee.fname,"Fred");
   strcpy(employee.phone,"812-123-4567");
   cout << "Writing employee record: " << endl;
   cout << employee.fname << " " << employee.lname << endl;
   cout << employee.phone << endl;

   // content datum points to the employee data
   content.dptr = (char *)(&employee);
   content.dsize = sizeof(employee);
   // Fill in the key struct
   keydata.id = employee.id;
   keydata.type = EMPREC;

   // Write the employee record
   gdbm_store(dbf, key, content, GDBM_REPLACE);

   // Fill salary struct
   salary.id = employee.id;
   salary.salary = 1234;
   cout << "Writing salary record." << endl;
   
   // content datum now points to the salary data
   content.dptr = (char *)(&salary);
   content.dsize = sizeof(salary);

   // Fill in the key struct
   keydata.id = salary.id;
   keydata.type = SALREC;

   // Write salary record
   gdbm_store(dbf, key, content, GDBM_REPLACE);

   // Repeat with another employee
   employee.id = 43210;
   strcpy(employee.lname,"Rubble");
   strcpy(employee.fname,"Barney");
   strcpy(employee.phone,"812-321-7654");
   cout << "Writing employee record: " << endl;
   cout << employee.fname << " " << employee.lname << endl;
   cout << employee.phone << endl;

   content.dptr = (char *)(&employee);
   content.dsize = sizeof(employee);
   keydata.id = employee.id;
   keydata.type = EMPREC;
   gdbm_store(dbf, key, content, GDBM_REPLACE);

   salary.id = employee.id;
   salary.salary = 8888;
   cout << "Writing salary record." << endl;
   
   content.dptr = (char *)(&salary);
   content.dsize = sizeof(salary);
   keydata.id = salary.id;
   keydata.type = SALREC;
   gdbm_store(dbf, key, content, GDBM_REPLACE);

   gdbm_close(dbf);

   return 0;
}
