#define MAX_SIZE 20;
//start pin
pinStart1 pimode
//stop pin
pinStop1
//on pin
pinOn1
//off pin
pinOff1

//inst1
inst1
//inst2
inst2
//inst3
inst3
//inst4
inst4
//inst5
inst5

int loop1[MAX_SIZE];
int iter1=0;
int loop2[MAX_SIZE];
//int loop3[20];

void start(){

}

void loop(){
    //録音開始
    if(pinStart1  == HIGH){
        cnt1=0;
        record1 = 1;
    }
    //終了
    if(record1 == 1 && (pinStop1 == 1 || iter1 == MAX_SIZE-1 ) ){
        record1 = 0;
    }
    //再生開始
    if(on == 1){

    }
    //再生停止
    if(){
        
    }

    if(record1 == 1){
        //待ち時間を格納
        if(inst1 == HIGH){
            loop1[iter1] = cnt1;
            cnt1 = 0;
            iter1++;
        }
        //待ち時間++
        else{
            cnt1++;
        }
    }
    else if() {

    }
}
