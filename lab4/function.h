struct nodeClass
{
	int classID;
	double classMidtermAverage;
	struct nodeClass *next;
	struct nodeStudent *studentPtr;
};

struct nodeStudent
{
	int studentID;
	int midterm;
	struct nodeStudent *next;
};


// You must write all the function definitions to be used in this lab into this file.
// You may also write other functions that may be called from our functions.
// Do not make any changes to the main.c file.
// Upload function.h file to the system as StudentNumber.h.



