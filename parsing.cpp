/** Program written by Luis Ardila following the double Love slow cooking 
method, a first cooking step follow by a long fermentation and a post-cooking 
period. All this delivers an extraordinary taste of double cooked and fermented 
Love portion :*
email: leardilap@gmail.com
*/

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

#include <cstring>
#include <stdlib.h>

struct TrtSt 
{
   string grouping;
   string mean; //float
   string sampleN; //int
   string trtName;
};

TrtSt *pointerTrtSt = new TrtSt[20];

const int BiomarkersNum1 = 20, StatTestsNum = 4, TrtNum1 = 20;
const string StatGrouping[4] = {"t", "Duncan", "Tukey", "Scheffe"};
const string StatTest[4] = {  "t Tests (LSD) for ", 
                              "Duncan's Multiple Range Test for ", 
                              "Tukey's Studentized Range (HSD) Test for ",
                              "Scheffe's Test for "};

TrtSt DataStructure [BiomarkersNum1][StatTestsNum][TrtNum1];
string LSmeansSt [BiomarkersNum1][TrtNum1][TrtNum1];

string reduce( const string& str,
               const string& fill,
               const string& whitespace);
string trim(   const string& str,
               const string& whitespace);

void line2array(string& ReadReduced);
void words2structure(TrtSt** pointerTrtSt);
void printingScreen();
void printingFile();
int getTrtNumber();
  
ifstream Reading;

string ReadingName, Read, ReadReduced;
const int linelenght = 200;
string delimiter = " ";
char Buffer[linelenght];
string token;
string Trtnames[15];
string Biomarkers[15];  
string farray[15];
string test[15];
size_t pos = 0;             

int num, innerNum, i, TreatmentsReadNum, LSnum;
int o = 0, Bio = 0, Stat = 0, Trt = 0;
int ii = 0;
int BiomarkersNum;
int TrtNum;

          
int main(int argc, char** argv) {

   ReadingName = argv[1];
   
   Reading.open(ReadingName.c_str());  
	
	num = 0;
	innerNum = 0;
	
	//Reading one line at a time of the input file
	while (!Reading.eof()) {
	
      //reading each line until the character /n apears: meaning end of line
		Reading.getline(Buffer,linelenght,'\n');		
			
		//from char to string
		Read=Buffer;										
		//runing each line through the "reduce" function to 
		//get rid of extra espaces
		ReadReduced = reduce(Read, " ", " \t");
		
		//num is an indicator of the step we are in, first gather 
		//the number of Biomarkers, then the number of treatments and finally 
		//fill in the info for each
		switch (num) {
		
		//gathering the info for the biomarkers
				case 0 :
					//finding line with this words as begining
					if (ReadReduced.find("Obs Trt Rep") == 0) {	
				      line2array(ReadReduced);
				      //Biomarkers num minus the first three words
				      BiomarkersNum = ii - 3;
				      //cout << BiomarkersNum << endl;
				      for (i = 0; i < BiomarkersNum; i++) {		
						   //printing names with tabs
						   Biomarkers[i] = farray [ii-BiomarkersNum+i];
							//cout << Biomarkers [i] << "\t";				
						}
						cout << endl;
				      num++;
				   }
					break;
			   
			   //gathering info about the treatments, number and names
				case 1 :
					//finding line with this words as begining
					if (ReadReduced.find("Trt") == 0) {
				      line2array(ReadReduced);
				      istringstream ( farray[1] ) >> TrtNum;
				      //cout << TrtNum << endl;
				      for (i = 0; i < TrtNum; i++) {		
						   //printing names with tabs
						   Trtnames[i] = farray [ii-TrtNum+i];
							//cout << Trtnames [i] << "\t";				
						}
						//cout << endl;
				      num++;
				      
				      //Initializing the index for the DataStructure
				      Bio = 0;
				      Stat = 0;
				      Trt = 0;
				      /** printing
				      for (int a = 0; a < 4; a++)
				         cout << StatGrouping[a] << endl;
				      */   
				      
				   }
					break;

//###########################################################################
				//finding info for each biomarker, each probablility test and 
				//organizing the data inside each treatment name
				
				//case 2 is for t Tests (LSD)
				case 2 :
				   {
				   
				      switch (innerNum) {
				      
				         case 0 :
				            //finding line with this words as begining
					         if (ReadReduced.find(StatTest[Stat] + Biomarkers[Bio]) 
					         == 0) {
					            //cout << StatTest[Stat] << Biomarkers[Bio] << endl;
					            innerNum++;
					         }
					         break;
					      
					      case 1 :
					         if (ReadReduced.find(StatGrouping[Stat] + " Grouping") 
					         == 0) {
					            //cout << StatGrouping[Stat] << " Grouping" << endl; 
				               innerNum++;
				            }
				            break;
				         case 2 :
				            innerNum++; //empty space line
				            break;
				         case 3 :
				         {
				            line2array(ReadReduced);
			               
					         // Function to save the words in a line into the 
					         //structure of: 
					         // Grouping       Mean      N    Trt
					         words2structure(&pointerTrtSt);
					         
					         //increasing number of treatments already read
					         TreatmentsReadNum++;
					         
					         //if iqual to treatment num then go to next, else go 
					         //to next line 
					         if (TreatmentsReadNum == TrtNum) {
					            //cout << endl;					            
					            for (int a = 0; a < TrtNum; a++) {
					               DataStructure [Bio][Stat][a] = pointerTrtSt[a];
					               /** printing
					               cout  << pointerTrtSt[a].grouping << "\t" 
					                     << pointerTrtSt[a].mean << "\t" 
					                     << pointerTrtSt[a].sampleN << "\t" 
					                     << pointerTrtSt[a].trtName << endl; 
					               */     
                           }
                           /** Printing
                           for (int a = 0; a < TrtNum; a++) {
					               DataStructure [Bio][Stat][a] = pointerTrtSt[a];
					               cout << (DataStructure[Bio][Stat][a]).grouping 
					                    << "\t" << (DataStructure[Bio][Stat][a]).mean 
					                    << "\t" << (DataStructure[Bio][Stat][a]).sampleN 
					                    << "\t" << (DataStructure[Bio][Stat][a]).trtName 
					                    << endl;      
                           }
                           */
                           Stat++;
                           TreatmentsReadNum = 0;
                           innerNum = 0;
                           if (Stat == 4) {
                              Bio++;
                              Stat = 0;
                              if (Bio == BiomarkersNum) {
                                 num++;
                              }
                           }
					            
					         }
					         else {
					            innerNum = 2;	
					         }
					      }				      
					         break;
					         
					      default :
					            cout << "ERROR!!!!!!" << endl;
					         break;
					      
					   }  
				   }
				   break;				
				   
				default:
					break;
					
			}
				
		//cout << num << endl;
      //cout << ReadReduced << endl;
   }//end while
      
   Reading.close();
   Reading.open(ReadingName.c_str());  
	
	LSnum = 0;
	Bio = 0;
	TreatmentsReadNum = 0;
	
	//Reading one line at a time of the input file
	while (!Reading.eof()) {
	
      //reading each line until the character /n apears: meaning end of line
		Reading.getline(Buffer,linelenght,'\n');		
			
		//from char to string
		Read=Buffer;										
		//runing each line through the "reduce" function to 
		//get rid of extra espaces
		ReadReduced = reduce(Read, " ", " \t");
		
		//num is an indicator of the step we are in, first gather 
		//the number of Biomarkers, then the number of treatments and finally 
		//fill in the info for each
		switch (LSnum) {
		   case 0 :
            //finding line with this words as begining
            if (ReadReduced.find("Dependent Variable: " + Biomarkers[Bio]) 
            == 0) {
               //cout << ReadReduced << endl;
               LSnum++;
            }
            break;
         case 1 : 
            //blank line
            LSnum++;
            //cout << ReadReduced << " " << LSnum << endl;
            break;
         case 2 : 
            //number of words is numTrt + 1?
            //cout << ReadReduced << endl;
            line2array(ReadReduced);
            if (ii == TrtNum + 1) {
               LSnum++;
            }
            else
               LSnum = 0;   
            break;
         case 3 :
            //blank line
            LSnum++;
            break;
         case 4 :
            {
               //Trt info
               //cout << ReadReduced << endl;
               line2array(ReadReduced);
               int b = 1;
               for (int a = 0; a < TrtNum; a++) {
                  if (TreatmentsReadNum == a) {
                     LSmeansSt [Bio][TreatmentsReadNum][a] = " ";
                  }
                  else {
                     LSmeansSt [Bio][TreatmentsReadNum][a] = farray [b];
                     b++;
                  }
               }
               
               TreatmentsReadNum++;
               if (TreatmentsReadNum == TrtNum) {
                  Bio++;
                  TreatmentsReadNum = 0;
                  
                  if (Bio == BiomarkersNum) {
                     LSnum++;
                     
                  }
                  else {
                     LSnum = 0;
                  }
               }
            }
            break; 
         
         default :
            break;
      }//end switch LSnum
   }//end while
   Reading.close();
   printingScreen();
   printingFile();
   
   cout << "END" << endl;
   delete [] pointerTrtSt;
}
  
//-----------------------------------------------------------------------------
//#############################################################################
//FUNCTIONS

void line2array(string& ReadReduced) {
   ii = 0;				
   //while position is different to the end of string			
	while ((pos = ReadReduced.find(delimiter)) != string::npos) {	
		//save substring in token
		token = ReadReduced.substr(0, pos);				
		//erase from string the analyzed part saved in token		
		ReadReduced.erase(0, pos + delimiter.length());  
								
		farray[ii] = token;
		//incrementing i							
		ii++;												

	}//end of while
	
	farray[ii] = ReadReduced;
	ii++;
}

void words2structure(TrtSt** pointerTrtSt) {
   //defining temporary variable
   int switchLetter = 0;
   
   //Asigning a number depending on the initial letter of the line
   if (farray[0] == "A") 
      switchLetter = 1;
   else if (farray[0] == "B") 
      switchLetter = 2;
   else if (farray[0] == "C") 
      switchLetter = 3;
         
   int n1 = getTrtNumber();
   if (ii == 4){
      switch (switchLetter) {
         case 1 : 
            (*(pointerTrtSt[0]+n1)).grouping = " " + farray [0] + " |    |    ";
            break;
         case 2 : 
            (*(pointerTrtSt[0]+n1)).grouping = "    | " + farray [0] + " |    ";
            break;
         case 3 : 
            (*(pointerTrtSt[0]+n1)).grouping = "    |    | " + farray [0] + " ";
            break;
         default : 
            break;
      }
   }
   else if (ii == 5) {
      switch (switchLetter) {
         case 1 :
            if (farray[1] == "B") {
               // B is second after A
               (*(pointerTrtSt[0]+n1)).grouping = " " + farray [0] + " | " 
               + farray [1] + " |    ";
            }
            else {
               // C is second after A
               (*(pointerTrtSt[0]+n1)).grouping = " " + farray [0] + " |    | " 
               + farray [1] + " ";
            }
            break;
            
            break;
         case 2 :
            if (farray[1] == "A") {
               // A is second after B
               (*(pointerTrtSt[0]+n1)).grouping = " " + farray [1] + " | " 
               + farray [0] + " |    ";
            }
            else {
               // C is second after B
               (*(pointerTrtSt[0]+n1)).grouping = "    | " + farray [0] + " | " 
               + farray [1] + " ";
            }
            break;
         case 3 :
            if (farray[1] == "A") {
               // A is second after C
               (*(pointerTrtSt[0]+n1)).grouping = " " + farray [1] + " |    | " 
               + farray [0] + " ";
            }
            else {
               // B is second after C
               (*(pointerTrtSt[0]+n1)).grouping = "    | " + farray [1] + " | " 
               + farray [0] + " ";
            }
            break;
         default :
            break;
      }   
   }
   else if (ii == 6) {
      switch (switchLetter) {
         case 1 : 
            if (farray[1] == "B") {
               // B is second after A
               (*(pointerTrtSt[0]+n1)).grouping = " " + farray [0] + " | " 
               + farray [1] + " | " + farray [2] + " ";
            }
            else {
               // C is second after A
               (*(pointerTrtSt[0]+n1)).grouping = " " + farray [0] + " | " 
               + farray [2] + " | " + farray [1] + " ";
            }
            break;
         case 2 :
            if (farray[1] == "A") {
               // A is second after B
               (*(pointerTrtSt[0]+n1)).grouping = " " + farray [1] + " | " 
               + farray [0] + " | " + farray [2] + " ";
            }
            else {
               // C is second after B
               (*(pointerTrtSt[0]+n1)).grouping = " " + farray [2] + " | " 
               + farray [0] + " | " + farray [1] + " ";
            }
            break;
         case 3 :
            if (farray[1] == "A") {
               // A is second after C
               (*(pointerTrtSt[0]+n1)).grouping = " " + farray [1] + " | " 
               + farray [2] + " | " + farray [0] + " ";
            }
            else {
               // B is second after C
               (*(pointerTrtSt[0]+n1)).grouping = " " + farray [2] + " | " 
               + farray [1] + " | " + farray [0] + " ";
            }
            break;
         default :
            break;
      }   
   }
      
      (*(pointerTrtSt[0]+n1)).mean     = farray [ii-3];
      (*(pointerTrtSt[0]+n1)).sampleN  = farray [ii-2];
      (*(pointerTrtSt[0]+n1)).trtName  = farray [ii-1];
 
   /** printing
   for (int a = 0; a < TrtNum; a++) {
		cout << "Pre2 " << a << endl;
		cout  << (*pointerTrtSt[a]).grouping << "\t" 
		      << (*pointerTrtSt[a]).mean << "\t" 
		      << (*pointerTrtSt[a]).sampleN << "\t" 
		      << (*pointerTrtSt[a]).trtName << endl; 
	getchar();     
   } 
   */    
   
}

int getTrtNumber() {
   int n;

   for (int a = 0; a < TrtNum; a++) {
      
      if (Trtnames[a].compare(farray[ii-1]) == 0) {
         n = a;
         break;
      }
   }
   return n;   
}


string trim(const string& str,
            const string& whitespace = " \t") {
    const int strBegin = str.find_first_not_of(whitespace);
    if (strBegin == string::npos)
        return ""; // no content

    const int strEnd = str.find_last_not_of(whitespace);
    const int strRange = strEnd - strBegin + 1; //+1 for WINDOWS, 0 for LINUX

    return str.substr(strBegin, strRange);
}

string reduce(const string& str,
              const string& fill = " ",
              const string& whitespace = " \t") {
    // trim first
    string result = trim(str, whitespace);

    // replace sub ranges
    int beginSpace = result.find_first_of(whitespace);
    while (beginSpace != string::npos)
    {
        const int endSpace = result.find_first_not_of(whitespace, beginSpace);
        const int range = endSpace - beginSpace;

        result.replace(beginSpace, range, fill);

        const int newStart = beginSpace + fill.length();
        beginSpace = result.find_first_of(whitespace, newStart);
    }

    return result;
}	

void printingScreen (){
   for (int a = 0; a < BiomarkersNum; a++) {
      cout << endl;
      cout  << setw(7) << Biomarkers[a] << "|"
            << setw(14) << "LSD       " << "|"
            << setw(14) << "Duncan    " << "|"
            << setw(14) << "Tukey     " << "|"
            << setw(14) << "Scheffe   " << "|"
            << endl;
            
      cout  << setfill('-') << setw(68) << "-"
            << endl << setfill(' ');
            
      for (int b = 0; b < TrtNum; b++) {
         cout  << setw(7) << Trtnames[b] << "|"
               << setw(14) << (DataStructure[a][0][b]).grouping << "|"
               << setw(14) << (DataStructure[a][1][b]).grouping << "|"
               << setw(14) << (DataStructure[a][2][b]).grouping << "|"
               << setw(14) << (DataStructure[a][3][b]).grouping << "|"
               << endl;
      }
      cout << endl;
     			      
   }
   
   //LSmeans
   for ( int z = 0; z < BiomarkersNum; z++) {
      cout << setw(7) << Biomarkers[z] << "|";
      for (int a = 0; a < TrtNum; a++) {
         cout << setw(7) << Trtnames[a] << "|";
      }
      cout << endl;
      for (int a = 0; a < TrtNum; a++) {
         cout << setw(7) << Trtnames [a] << "|";
         for (int c = 0; c < TrtNum; c++) {
           cout << setw(7) << (LSmeansSt [z][a][c]) << "|";
         }
         cout << endl;
      }
      cout << endl;
   }
}

void printingFile (){
   ofstream Output;
   string OutputName;
   
   OutputName = ReadingName;
	
	//putting .csv for the output name
	OutputName.replace(OutputName.length() - 4, OutputName.length(), ".csv");	
	
	//putting Out- at the begining of the output file name
	OutputName.insert(OutputName.length() - 4, "-Out");												
	Output.open(OutputName.c_str());
	
	
   for (int a = 0; a < BiomarkersNum; a++) {
      Output << endl;
      Output   << Biomarkers[a]
               << ",LSD"
               << ",Duncan"
               << ",Tukey"
               << ",Scheffe"
               << ",," << Biomarkers[a];
               
      for (int aa = 0; aa < TrtNum; aa++) {
         Output << "," << Trtnames[aa];
      }  
      Output << endl;
            
      for (int b = 0; b < TrtNum; b++) {
         Output  << Trtnames[b]
            << "," << (DataStructure[a][0][b]).grouping
            << "," << (DataStructure[a][1][b]).grouping
            << "," << (DataStructure[a][2][b]).grouping
            << "," << (DataStructure[a][3][b]).grouping
            << ",,"<< Trtnames [b];
         for (int c = 0; c < TrtNum; c++) {
            Output << "," << (LSmeansSt [a][b][c]);
         }
         Output << endl;   
      }
            
   }
   Output.close();
}


//Interesting function for printing each char of a c++ string 
//   for (std::string::iterator it = farray[ii-1].begin(); 
//   it != farray[ii-1].end(); ++it)
//         cout << "ITfarray " << *it << endl;         
