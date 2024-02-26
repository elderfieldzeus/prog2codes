# Things to remember for file handling
### Modes
- **"r"** = read
- **"w"** = write / create
- **"a"** = append
- **"r+"** = read and write
- **"w+"** = read and write
- **"a+"** = read and append
- **"rb"** = read binary
- **"wb"** = write binary
- **"ab"** = append binary
- **"rb+"** = read and write binary
- **"wb+"** = read and write binary
- **"ab+"** = read and append binary

### Functions
- **fopen("filename", "mode")** => links file to program => {e.g. FILE *fptr = fopen("text.txt", "w");}
- **fclose(nameOfFilePointer)** => cuts link between file and program => {e.g. fclose(fptr);}
- **fread(pointerToDestination, sizeOfDataType, numOfElems, nameOfFilePointer)** => reads data from a physical file => {e.g fread(&age, sizeof(int), 1, fptr);}
- **fwrite(pointerToSourcem sizeOfDataType, numOfElems, nameOfFilePointer)** => writes data to physical file => {e.g. fwrite(name, sizeof(char), strlen(name) + 1, fptr);}
- **rewind(nameOfFilePointer)** => returns cursor back to the start of the file => {e.g. rewind(fptr);}
- **remove("filename")** => removes file.
- **rename("oldFileName", "newFileName")** => rename the file.

### Take Note
- **fread()** and **fwrite()** are not limited to arrays, or scalar variables, they can also be applied to structures => {e.g. fread(LIST, sizeof(ListType), 1, fptr);}
- **fopen()** returns NULL when file is not read or present.
