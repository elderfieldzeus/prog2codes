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
1) **FILE \*fopen("filename", "mode")**
   - links file to program
   - e.g. FILE *fptr = fopen("text.txt", "w");
2) **int fclose(nameOfFilePointer)**
   - cuts link between file and program
   - e.g. fclose(fptr);
3) **size_t fread(pointerToDestination, sizeOfDataType, numOfElems, nameOfFilePointer)** 
    - reads data from a physical file
    - e.g fread(&age, sizeof(int), 1, fptr);
4) **size_t fwrite(pointerToSourcem sizeOfDataType, numOfElems, nameOfFilePointer)**
   - writes data to physical file
   - e.g. fwrite(name, sizeof(char), strlen(name) + 1, fptr);
5) **int fseek(nameOfFilePointer, sizeInBytes, origin)**
   - moves current position in the file
   - e.g. fseek(fptr, 3*sizeof(structure), SEEK_CUR);
    - **ORIGINS:**
      - ***SEEK_SET or 0*** => start of the file
      - ***SEK_CUR or 1*** => current position
      - ***SEEK_END or 2*** => end of the file
        
6) **void rewind(nameOfFilePointer)**
    - returns cursor back to the start of the file
    - e.g. rewind(fptr);
7) **int remove("filename")** 
    - removes file.
    - e.g. remove("tasks.dat");
8) **int rename("oldFileName", "newFileName")** 
    - rename the file.
    - e.g. rename("files.dat", "newFile.dat");

### Take Note
- **fread()** and **fwrite()** are not limited to arrays, or scalar variables, they can also be applied to structures => {e.g. fread(LIST, sizeof(ListType), 1, fptr);}
- **fopen()** returns NULL when file is not read or present.
