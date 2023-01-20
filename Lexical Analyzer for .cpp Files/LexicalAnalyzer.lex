%{
    int lineNum = 0;

    void printResultsToFile(char *TextType, char *Text)
    {
        FILE *fptr;
        fptr = fopen("results.txt", "a+");

        fprintf(fptr, "\t%sLine Number: %i\t\t%s\n", TextType, lineNum, Text);
        fclose(fptr);
    }
%}

Delimitor [ \t;]*
Header "#include "[<"].*[>"]
Namespace "using namespace std"
ReservedWord if|else|for|while|do|delete|new|main|return|private|public|case|switch|break|cout|cin|endl|virtual

Digit [0-9]
UC_Alphabet [A-Z]
LC_Alphabet [a-z]
Alphabet {UC_Alphabet}|{LC_Alphabet}
Symbol [_.\-/$]
Dot \.

DataType int|string|void|float|char|double|bool|"unsigned int"
Bool true|false|0|1
Int [+-]?{Digit}+
Float [+-]?{Digit}*{Dot}{Digit}*
Char {Alphabet}|{Digit}|{Symbol}
String \"[^\n"]+\"

Bracket [()\[\]{}]
Operator [+\-\*/\^%=]|"<<"|">>" 
SingleLineComment "//".*
MultiLineComment "/*"(.|\n)*?"*/"
Comment {SingleLineComment}|{MultiLineComment}
Var {Alphabet}*|{Digit}*|{Symbol}*
Variable {Alphabet}{Var}*
Array {Variable}\[.*\]
ConditionUtility [><]|">="|"<="|"=="|"!="
Number {Digit}+

Condition \({Variable}" "{ConditionUtility}" "{Variable}\)|\({Variable}" "{ConditionUtility}" "{Number}\)|
DeclareFunction {DataType}" "{Variable}\(.*\)
FunctionCall {Variable}\(.*\)
Struct "struct"" "{Variable}
Class "class"" "{Variable}
Template "template <typename "{Variable}>
FriendFunction "friend "{DataType}" "{Variable}\(.*\)
FriendClass "friend class "{Variable}
AccessSpecifier public|private|protected
InheritanceUtility ", "{AccessSpecifier}" "{Variable}
Inheritance "class"" "{Variable}" : "{AccessSpecifier}" "{Variable}{InheritanceUtility}*
PointerDeclaration [*]{Variable}
PointerAddress [&]{Variable}
PointerArrow "->"
Pointer {Variable}{PointerArrow}{Variable}


%%

{Delimitor} {;}
{Comment} {printResultsToFile("Comment\t\t\t\t",yytext);}
{Header} {printResultsToFile("Header\t\t\t\t",yytext);}
{Namespace} {printResultsToFile("Namespace\t\t\t",yytext);}
{ReservedWord} {printResultsToFile("Reserved Word\t\t",yytext);}
{DataType} {printResultsToFile("Datatype\t\t\t",yytext);}
{Bracket} {printResultsToFile("Brackets\t\t\t",yytext);}
{Bool} {printResultsToFile("Boolean\t\t\t\t",yytext);}
{Float} {printResultsToFile("Float\t\t\t",yytext);}
{Int} {printResultsToFile("Integer\t\t\t\t",yytext);}
{String} {printResultsToFile("String\t\t\t\t",yytext);}
{Char} {printResultsToFile("Character\t\t\t",yytext);}
{Operator} {printResultsToFile("Operator\t\t\t",yytext);}
{Array} {printResultsToFile("Array\t\t\t\t",yytext);}
{PointerDeclaration} {printResultsToFile("Declare Pointer\t\t",yytext);}
{PointerAddress} {printResultsToFile("Pointer Address\t\t",yytext);}
{Pointer} {printResultsToFile("Pointer\t\t\t\t",yytext);}
{DeclareFunction} {printResultsToFile("Declare Function\t",yytext);}
{FunctionCall} {printResultsToFile("Function Call\t\t",yytext);}
{Struct} {printResultsToFile("Structure\t\t\t",yytext);}
{Class} {printResultsToFile("Class\t\t\t\t",yytext);}
{Template} {printResultsToFile("Template\t\t\t",yytext);}
{FriendClass} {printResultsToFile("Friend Class\t\t",yytext);}
{FriendFunction} {printResultsToFile("Friend Function\t\t",yytext);}
{Inheritance} {printResultsToFile("Inheritance\t\t\t",yytext);}
{Condition} {printResultsToFile("Condition\t\t\t",yytext);}
{Variable} {printResultsToFile("Variable\t\t\t",yytext);}

\n {lineNum++;}

%%

int yywrap(){}

int main()
{
    FILE *fptr;
    fptr = fopen("results.txt", "w");
    fclose(fptr);

    FILE *fout;

    fout = fopen("Sample1.cpp","r");
    lineNum=0;
    printResultsToFile("FILE 1\t\t\t\t","Sample1.cpp\n");
    lineNum++;
    yyin = fout;
    yylex();

    fout = fopen("Sample2.cpp","r");
    lineNum=0;
    printResultsToFile("\n\n\tFILE 2\t\t\t\t","Sample2.cpp\n");
    lineNum++;
    yyin=fout;
    yylex();

    fout = fopen("Sample3.cpp","r");
    lineNum=0;
    printResultsToFile("\n\n\tFILE 3\t\t\t\t","Sample3.cpp\n");
    lineNum++;
    yyin=fout;
    yylex();

     fout = fopen("Sample4.cpp","r");
    lineNum=0;
    printResultsToFile("\n\n\tFILE 4\t\t\t\t","Sample4.cpp\n");
    lineNum++;
    yyin=fout;
    yylex();

    return 0;
}
