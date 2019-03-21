/* 
* Problem 10 of Chapter 16
* by DIAO Zhongpu
* To avoid repeatedly display the feedback (or "Judge the Answer"),
* this project add an element "ptext" in the structure *questionT, 
* which is specially used for storing the feedback.
* And by adding a new fucntion JudgeAnswer (q), we seperate the display
* of feedback from that of question. Therefore we can only show the 
* feedback only after wrong answer has been input, fullfilling the 
* requirement.
* The cs.txt was changed correspondingly.
*
*/

/*
* File: teach.c
* -----------------
* This program executes a simple programmed instruction course. 
* The course is specified by a data file containing all the
* course information. The data structures and the format of
* the data file are described in Chapter 16.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "genlib.h"
#include "strlib.h"
#include "simpio.h"
#include "exception.h"

/*
* Constants
* -------------
* MaxQuestions -- Maximum question number
* MaxLinesPerQuestion -- Maximum number of lines per question
* MaxAnswersPerQuestion -- Maximum answers per question
* EndMarker -- String marking end of question text
*/

#define MaxQuestions 100
#define MaxLinesPerQuestion 20
#define MaxAnswersPerQuestion 10
#define EndMarker "-----"

/* Data structures */
/*
* Type: answerT
* --------------------
* This structure provides space for each possible answer 
* to a question.
*/

typedef struct{
    string ans;
    int nextq;
} answerT;

/*
* Type: questionT
* ---------------------
* This structure provides space for all the information
* needed to store one of the individual question records. 
* Because this structure is large ad it makes sense
* to refer to it as a single entity , questionT is defined
* as a pointer type.
*/

typedef struct{
	string ptext[MaxLinesPerQuestion+1];
    string qtext[MaxLinesPerQuestion+1];
    answerT answers[MaxAnswersPerQuestion];
    int nAnswers;
} *questionT;

/*
* type: courseDB
* --------------------
* This type is used to define the entire database, which is 
* a pointer to a record containing the title and an array of 
* questions.
*/

typedef struct{
    string title;
    questionT questions[MaxQuestions+1];
} *courseDB;

/* Private function declarations */

static courseDB ReadDataBase (void);
static bool ReadOneQuestion (FILE *infile, courseDB course); 
static void ReadQuestionText (FILE *infile, questionT q);
static void ReadAnswers (FILE *infile, questionT q);

static FILE *OpenUserFile (string prompt, string mode); 
static void ProcessCourse (courseDB course);
static void AskQuestion (questionT q);
static void JudgeAnswer (questionT q);
static int FindAnswer (string ans, questionT q);


/* Main program */

int main() {
    courseDB course;
    course = ReadDataBase ();
    ProcessCourse (course);
    return 0;
}

/* Section 1 ¨C Functions to read the data file */
/*
* Function: ReadDataBase
* Usage: ReadDataBase ();
* ----------------------------------
* This function asks the user for a file name and reads 
* in the database for the course. The file is formatted 
* as discussed in the section "Designing the external
* structures" in Chapter 16.
*/

static courseDB ReadDataBase (void)
{
    FILE *infile; courseDB course;
    infile = OpenUserFile ("Enter name of course: ", "r");
    course = New (courseDB);
    course->title = ReadLine (infile);
    while (ReadOneQuestion (infile, course));
    fclose (infile);
    return (course);
}


/*
* Function: ReadOneQuestion
* Usage: while (ReadOneQuestion (infile, course));
* ----------------------------------------------------------------
* This function reads in a single question from infile into the
* course data structure. As long as the complete question is
* read successfully, this function returns TRUE. When the end 
* of the file is encountered, the function returns FALSE.
* Thus, the "Usage" line above reads the entire data file.
*/

static bool ReadOneQuestion (FILE *infile, courseDB course) {
    questionT question;
    string line;
    int qnum;

    line = ReadLine (infile);
    if (line == NULL) return (FALSE);
    qnum = StringToInteger(line);
    if (qnum < 1 || qnum > MaxQuestions) {
        Error ("Question number % d out of range", qnum);
    }
    question = New (questionT); 
	ReadQuestionText (infile, question);
    ReadAnswers (infile, question);
    course->questions[qnum] = question;
    return (TRUE);
}

/*
* Function: ReadQuestionText
* Usage: ReadQuestionText (infile, question);
* ----------------------------------------------------------
* This function reads the text of the question into the
* question data structure which must have been allocated 
* by the caller. The end of the question text is signaled
* by a line matching the string EndMarker.
*/


static void ReadQuestionText (FILE *infile, questionT q) {
    string line;
    int nlines;

    nlines = 0;
    while (TRUE) {				// judge answer
        line = ReadLine (infile);
        if (StringEqual (line, EndMarker)) break;
        if (nlines == MaxLinesPerQuestion) {
            Error ("Too many lines");
        }
        q->ptext[nlines] = line;
        nlines++;
    }
    q->ptext[nlines] = NULL;
    nlines = 0;
    while (TRUE) {
        line = ReadLine (infile);
        if (StringEqual (line, EndMarker)) break;
        if (nlines == MaxLinesPerQuestion) {
            Error ("Too many lines");
        }
        q->qtext[nlines] = line;
        nlines++;
    }
    q->qtext[nlines] = NULL;
}


/*
* Function: ReadAnswers
* Usage: ReadAnswers (infile, question);
* ----------------------------------------------------
* This funtion reads the answer pairs for the question
* from the input ifle. Each answer consists of a stirng
* followed by a colon, followed by the number of the next 
* question to be read. The end of the answer list is
* signaled by a blank line or the end of the file.
*/

static void ReadAnswers (FILE *infile, questionT q) {
    string line, ans;
    int len, cpos, nextq, nAnswers;
    
    nAnswers = 0;
    while ((line = ReadLine (infile)) != NULL && (len = StringLength (line)) != 0) {
        cpos = FindChar (':', line, 0);
        if (cpos == -1) Error ("Illegal answer format");
        ans = SubString (line, 0, cpos - 1);
        nextq = StringToInteger (SubString (line, cpos+1, len-1));
        q->answers[nAnswers].ans = ConvertToUpperCase (ans);
        q->answers[nAnswers].nextq = nextq;
        nAnswers++;
    }
    q->nAnswers = nAnswers;
}

/*
* Function: OpenUserFile
* Usage: fileptr = OpenUserFile (prompt, mode);
* --------------------------------------------------------------
* This function prompt the user for a file name using the
* prompt string supplied by the user and then attempts to
* open that file with the specified mode. If the file is
* opened successfully, OpenUserFile returns the appropriate
* file pointer. If the open operation fails, the user is
* informed of the failure and given an opportunity to enter
* another file name.
*/

static FILE *OpenUserFile (string prompt, string mode)
{
    string filename;
    FILE *result;

    while (TRUE) {
    printf ("%s", prompt);
    filename = GetLine ();
    result = fopen (filename, mode);
    if (result != NULL) break;
        printf ("Can't open the file \"%s\"\n", filename);
    }
    return (result);
}

/* Section 2 ¨C Functions to process the course */
/*
* Function: ProcessCourse
* Usage: ProcessCourse (course);
* -------------------------------------------
* This function processes the course supplied by the caller.
* The basic operation consists of a loop that (a) prints out
* the current question, (b) reads in an answer, (c) looks up
* the answer in the database, and (d) goes to a new question 
* on the basis of that answer. In this implementation, the
* variable qnum holds the index of the question and the
* variable q holds the actual question data structure. The
* course always begins with question #1, after which the
* order is determined by the answers.
*/

static void ProcessCourse (courseDB course) {
    questionT q;
    int qnum;
    string ans;
    int index;
    int askagain=0;	/* 
					* New variable to record whether latter answer is 
					* processed correctly , in order to determine if 
					* responds to previous question should be displayed.
					*/

    printf ("%s\n", course->title);
    qnum = 1;
    while (qnum != 0) {
        q = course->questions[qnum];
        if(askagain){
        	;
		} else {
			JudgeAnswer(q);
		}
        AskQuestion (q);
        ans = ConvertToUpperCase (GetLine ());
        index = FindAnswer (ans, q);
        if (index == -1) {
            printf ("I don't understand that.\n");
            askagain=1;			// set to 1 when the question needs restating
        } else {
            qnum = q->answers[index].nextq;
            askagain=0;			// back to 0 when proceeding to next question
        }
    }
}

/*
* Functin: AskQuestion
* Usage: AskQuestion (q);
* --------------------------------
* This function asks the question indicate by the questionT 
* specified by q. Asking the question consists of displaying 
* each of the lies that comprise the question text.
*/

static void AskQuestion (questionT q)
{
    int i;

    for (i = 0; q->qtext[i] != NULL; i++) {
      	printf("%s\n", q->qtext[i]);
   	}
	
}

/*
* Functions: JudgeAnswer
* Usage: JudgeAnswer (q);
* --------------------------------
* This function judge player's last answer, which display the message
* seperated by EndMarker from next question in the files.
*/

static void JudgeAnswer (questionT q)
{
    int i;

    for (i = 0; q->ptext[i] != NULL; i++) {
      	printf("%s\n", q->ptext[i]);
   	}
	
}


/*
* Functions: FindAnswer
* Usage: FindAnswer (ans, q)
* -------------------------------------
* This function looks up the string ans in the list of answers 
* for question q. If the answer is found, its index in the
* answer list is returned. If not, the function returns ¨C1.
* The function uses a simple linear search algorithm to look 
* thought the array .
*/

static int FindAnswer (string ans, questionT q) {
    int i;

    for (i = 0; i < q->nAnswers; i++) {
        if (StringEqual (ans, q->answers[i].ans)) return (i);
    }
    return (-1);
}
