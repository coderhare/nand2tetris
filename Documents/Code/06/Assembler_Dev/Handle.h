//
// Created by Morisummer on 2021/10/16.
//

#ifndef ASSEMBLER_DEV_HANDLE_H
#define ASSEMBLER_DEV_HANDLE_H

/**
 * 把布局什么的集成到类里头，然后去调用处理函数
 */

//符号表
unordered_map <string, int> symbol_table{
        {"R0", 0}, {"R1", 1}, {"R2", 2}, {"R3", 3}, {"R4", 4},
        {"R5", 5}, {"R6", 6}, {"R7", 7}, {"R8", 8}, {"R9", 9},
        {"R10", 10}, {"R11", 11}, {"R12", 12}, {"R13", 13}, {"R14", 14},
        {"R15", 15},
        {"SCREEN", 16384}, {"KBD", 24576},
        {"SP", 0}, {"LCL", 1}, {"ARG", 2}, {"THIS", 3}, {"THAT", 4}
};

unordered_map <string, int> symbol_table_copy{
        {"R0", 0}, {"R1", 1}, {"R2", 2}, {"R3", 3}, {"R4", 4},
        {"R5", 5}, {"R6", 6}, {"R7", 7}, {"R8", 8}, {"R9", 9},
        {"R10", 10}, {"R11", 11}, {"R12", 12}, {"R13", 13}, {"R14", 14},
        {"R15", 15},
        {"SCREEN", 16384}, {"KBD", 24576},
        {"SP", 0}, {"LCL", 1}, {"ARG", 2}, {"THIS", 3}, {"THAT", 4}
};


//变量表
unordered_map <string, int> variables;

//comp位域映射表
unordered_map <string, string> comp{
        {"0", "0101010"}, {"1", "0111111"}, {"-1", "0111010"}, {"D", "0001100"}, {"A", "0110000"},
        {"M", "1110000"}, {"!D", "0001101"}, {"!A", "0110001"}, {"!M", "1110001"},
        {"-D", "0001111"}, {"-A", "0110011"}, {"-M", "1110011"}, {"D+1", "0011111"}, {"A+1", "0110111"},
        {"M+1", "1110111"}, {"D-1", "0001110"}, {"A-1", "0110010"}, {"M-1", "1110010"}, {"D+A", "0000010"},
        {"D+M", "1000010"}, {"D-A", "0010011"}, {"D-M", "1010011"}, {"A-D", "0000111"}, {"M-D", "1000111"},
        {"D&A", "0000000"}, {"D&M", "1000000"}, {"D|A", "0010101"}, {"D|M", "1010101"},{"1+D", "0011111"},
        {"1+A", "0110111"}, {"1+M", "1110111"}, {"A+D", "0000010"}, {"M+D", "1000010"}, {"A&D", "0000000"}, {"M&D", "1000000"}, {"A|D", "0010101"}, {"M|D", "1010101"}
};


//dest位域映射表
unordered_map<string, string> dest{
        {"null", "000"}, {"M", "001"}, {"D", "010"}, {"MD", "011"}, {"A", "100"}, {"AM", "101"},
        {"AD", "110"}, {"AMD", "111"}, {"DM", "011"}, {"MA", "101"}, {"DA", "110"}, {"MAD", "111"}, {"MDA", "111"},
};


//jmp位域映射表
unordered_map<string, string> jump{
        {"null", "000"}, {"JGT", "001"}, {"JEQ", "010"}, {"JGE", "011"}, {"JGT", "100"},
        {"JNE", "101"}, {"JLE", "110"}, {"JMP", "111"}
};


unordered_set <char> valid{
    '+', '-','=',';', '@','(',')', '_', '|', '&', '!'
};

int allocate = 16;  //设定的一个可以分配内存的起点

void op(string & filename){
    cout << filename << '\n';
    //每一次操作都要重置符号表以及变量表
    symbol_table = symbol_table_copy;
    variables.clear();
    allocate = 16;
}

string & outputfilename(string  filename){
    while(filename.size() && filename.back() != '.') filename.pop_back();
    filename += "hack";
    return filename;
}

bool isvalid(char & c){
    return isalnum(c) || valid.count(c);
}


/**
 * Parser module
 */
namespace Parser {

    char CommandType(string &str) {
        int i = 0, n = str.size();
        if(i == n) return 'N'; //Null line
        if(str[i] == '@'){
            int j = i + 1;
            if(isdigit(str[j])) return 'A';        //A instruction
            return 'L';                            //L instruction
        }
        else if(str[i] == '/') return '/';         //comments
        else if(str[i] == '(') return '(';         //symbols
        return 'C';                                //C instruction
    }

    string  skip(string str) {
        string ans;
        for(char & c: str){
            if(c == '/') return ans;  //comments
            if(!valid.count(c) && !isalnum(c)) continue;  //偷懒，因为asm的语法比较简单，只支持较少的符号，所以为了避免对控制字符等的处理，而采取判断合法字符的方式
            ans += c;
        }
        return ans;
    }
}
/**
 * Code module
 */
namespace Code{
    string A(int val){
        string ans;
        while(val){
            if(val & 1) ans += '1';
            else ans += '0';
            val >>= 1;
        }
        int zero = 16 - ans.size();   //二进制字符串的长度为16
        while(zero--) ans += '0';
        reverse(begin(ans), end(ans));
        return ans;
    }
    string C(string command){
        //C指令的解析稍微麻烦些
        //需要分为 dest=comp;jmp位域然后解析后再拼接
        int i = 0, n = command.size();
        int dest_pos = 0, jmp_pos = n;
        for(i = 0; i < n; i++) {
            char &c = command[i];
            if (c == '=') dest_pos = i;
            else if(c ==  ';') jmp_pos = i;
        }
        string d, jmp, cmp;
        //if '=' exists, then dest exists.
        if(dest_pos != 0){
            i = 0;
            while(i != dest_pos) d += command[i++];
        }
        else{
            d = "null";
        }
        //if ';' exists, then jump exists
        //get the comp part
        i = dest_pos;
        if(d != "null") i++; //skip '='
        while(i < jmp_pos && command[i] != '\r') cmp += command[i++];
        //get the jmp part
        i = jmp_pos + 1;
        while(i < n && command[i] != '\r') jmp += command[i++];
        if(jmp.empty()) jmp = "null";
        if((comp[cmp] + dest[d] + jump[jmp]).size() < 13) {

            cout <<command << ' ' << cmp << ' ' << cmp.size() << '\n';
        }
        return "111" +  comp[cmp] + dest[d] + jump[jmp];
    }
}

bool handle(string & filename){
    ifstream ifs;
    ofstream ofs;
    string outputfile = outputfilename(filename) + '1';
    ifs.open(filename, ios::in);
    ofs.open(outputfile, ios::out);
    if(!ifs.is_open()) {
        cout << "Open failure" << endl;
        return false;
    }
    string line;
    //first pass
    int LineCount = 0;
    while(getline(ifs, line)){
        //if(line.size() == 1 && (line[0] >= 0 && line[0] <= 31)) continue;  //这一句意思是控制字符都去除，主要是一开始没分清换行和回车，unix和Windows的不一样，控制字符分布区间为[0,31]
        string line1 = Parser::skip(line);   //skip whitespaces && comments
        //cout << line1 << '\n';
        if(line1.size() == 0) continue;
        //cout << LineCount << ' ' << line1 << '\n';
        char commandtype = Parser::CommandType(line1);
        if(commandtype == '/') continue;
        else if(commandtype == '('){             //store the symbols
            int i = 1;
            string symbol;
            while(i < line1.size() && isvalid(line1[i])) symbol += line1[i++];
            symbol.pop_back(); //erase ')'
            symbol_table[symbol] = LineCount;
            //cout << symbol << ' ' << LineCount << '\n';
            continue;
        }
        else{
//          cout << line1 << '\n';
//           cout << ":" << line1.size() << '\n';
            ofs << line1 << '\n';
        }

        LineCount++;
    }
    ifs.close();
    ofs.close();
    //第二次遍历second pass
    //这一次主要是将标记和变量区分开来，并且，将代码转换为二进制串
    ifs.open(outputfile, ios::in);
    outputfile.pop_back();
    ofs.open(outputfile, ios::out);
    int cnt = 0;
    while(getline(ifs, line)){
        char commandtype = Parser::CommandType(line);
        cnt++;
        if(line == "M=DM") cout << cnt << '\n';
        if(commandtype == 'A'){
            //A instruction
            ofs << Code::A(stoi(line.substr(1, line.size() - 1))) << '\n';  //to Binary code
        }
        else if(commandtype == 'L'){
            //L instruction
            string ss = line.substr(1, line.size() - 1); //还要去除末尾的换行符
            if(symbol_table.count(ss)){
                //marks
                ofs << Code::A(symbol_table[ss]) << '\n';
            }
            else{
                //variable.
                // we need to search the available area and allocate it
                if(variables.count(ss) == 0) variables[ss] = allocate++;
                ofs << Code::A(variables[ss]) << '\n';
            }
        }
        else{
            //C instruction
            ofs << Code::C(line) << '\n';
        }
    }
    ifs.close();
    return true; //if nothing happens
}

#endif //ASSEMBLER_DEV_HANDLE_H
