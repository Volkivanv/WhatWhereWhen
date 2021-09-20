#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

std::string to_lower(std::string text) {
    std::transform(text.begin(), text.end(), text.begin(), ::tolower);
    return text;
}
void readPos(long long* qPos, std::string filePath){
    std::ifstream  textFile;
    textFile.open(filePath, std::ios::binary);
    if(textFile) {
        int i = 0;
        while (!textFile.eof()) {
            char c;
            textFile.read(&c, sizeof(c));
            //std::cout << c;
            if(c == '<'){
              //  std::cout << textFile.gcount()  ;
                *(qPos+i) = textFile.tellg();
              //  std::cout << *(qPos+i) << std::endl;
                i++;
            }
        }
        textFile.close();
    }else {
        std::cerr << "File is not found!" << std::endl;
    }

}

std::string getTextFromFile(long long* ar, int phraseNum, std::string filePath){
    std::string strBuf = "";
    std::ifstream  textFile;
    textFile.open(filePath, std::ios::binary);
    if(textFile) {
        textFile.seekg(*(ar+phraseNum));


        while (!textFile.eof()){
            char c;
            textFile.read(&c, sizeof(c));

            if(c == '>') break;
            strBuf+=c;
        }
        textFile.close();
    }else {
        std::cerr << "File is not found!" << std::endl;
    }
    return strBuf;
}

//bool allAns(bool* b){
//    for(int i = 0; i < 13;i++){
//        if(*(b+i)) return false;
//    }
//    return true;
//}

int main() {

    std::string filepathQuestions = "Questions.txt";
    std::string filepathAnswers = "Answers.txt";

    long long qPos[13];
    long long aPos[13];
    bool pQ[13];
    std::string answer;
    std::string realAnswer;
    for(int i = 0; i < 13; i++){
        pQ[i] = true;
    }
    readPos(qPos, filepathQuestions);
    readPos(aPos, filepathAnswers);
    int n = 0;
    int expertsPoints = 0;
    int viewersPoints = 0;
    while((expertsPoints < 6 )&&(viewersPoints < 6)){
        int offset;

        std::cout << "Please input offset!"<<std::endl;

        std::cin >> offset;
        n = (n+offset) % 13;
        while(!pQ[n]){
            n++;
            n%=13;
        }
        std::cout << getTextFromFile(qPos, n, filepathQuestions) << std::endl;
        realAnswer = getTextFromFile(aPos, n, filepathAnswers);
       // std::cout << realAnswer << std::endl;

        std::cout << "Input you answer!" << std::endl;


        std::cin >> answer;
        answer = to_lower(answer);

        if (answer == realAnswer) {
            std::cout << "You won the question!" << std::endl;
            expertsPoints++;
        } else {
            std::cout << "You lost the question! Right answer is: " << realAnswer <<std::endl;
            viewersPoints++;
        }
        std::cout << "Game score is Experts - "<< expertsPoints << ": Viewers - " <<viewersPoints << std::endl;
        pQ[n] = false;
    }

    if(expertsPoints > viewersPoints){
        std::cout << "Experts won!" << std::endl;
    } else {
        std::cout << "Viewers won!" << std::endl;
    }



    return 0;
}
