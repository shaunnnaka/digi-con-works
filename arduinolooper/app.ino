#define MAX_SIZE 20
//State Machine
#define S_RECORD_IDLE 0
#define S_RECORD_START 1
#define S_PLAY_IDLE 0
#define S_PLAY_START 1
/*
TODO
itermaxの実装
もろもろのエラー処理
--done

*/
//int -32768 32767
//start pin
const int pinRecordStart = 1; 
const int pinRecordStop = 1; 
const int pinPlayStart = 1; 
const int pinPlayStop = 1; 
const int pinInst1 = 1; 
const int pinInst2 = 1; 
const int pinInst3 = 1; 
const int pinInst4 = 1; 

//配列のイテレータ
char iterRecordInst1=0;
char iterRecordInst2=0;
char iterRecordInst3=0;
char iterRecordInst4=0;
char iterPlayInst1=0;
char iterPlayInst2=0;
char iterPlayInst3=0;
char iterPlayInst4=0;
//RECORDした時のサイズ
char iterMax1=0;
char iterMax2=0;
char iterMax3=0;
char iterMax4=0;
//待ち時間カウンタ
int cntRecordInst1=0;
int cntRecordInst2=0;
int cntRecordInst3=0;
int cntRecordInst4=0;
int cntPlayInst1=0;
int cntPlayInst2=0;
int cntPlayInst3=0;
int cntPlayInst4=0;
int loopInst1[MAX_SIZE];
int loopInst2[MAX_SIZE];
int loopInst3[MAX_SIZE];
int loopInst4[MAX_SIZE];
bool FFInst1[] = {LOW, LOW};
bool FFInst2[] = {LOW, LOW};
bool FFInst3[] = {LOW, LOW};
bool FFInst4[] = {LOW, LOW};
bool InstOn1 = false;
bool InstOn2 = false;
bool InstOn3 = false;
bool InstOn4 = false;
char curRecord;
char curPlay;
bool error;
void start(){
    pinMode(pinRecordStart  , INPUT_PULLUP);
    pinMode(pinRecordStop   , INPUT_PULLUP);
    pinMode(pinPlayStart    , INPUT_PULLUP);
    pinMode(pinPlayStop     , INPUT_PULLUP);
    char curRecord = S_RECORD_IDLE;
    char curPlay = S_PLAY_IDLE;
    bool error = false;
    InstOn1 = false;
    InstOn2 = false;
    InstOn3 = false;
    InstOn4 = false;
    for (int i = 0; i < MAX_SIZE; i++){
        loopInst1[i] = -1;
        loopInst2[i] = -1;
        loopInst3[i] = -1;
        loopInst4[i] = -1;
    }
}

void loop(){
    //FF二段でpulldown
    FFInst1[1] = FFInst1[0];
    FFInst2[1] = FFInst2[0];
    FFInst3[1] = FFInst3[0];
    FFInst4[1] = FFInst4[0];
    FFInst1[0] = digitalRead(pinInst1);
    FFInst2[0] = digitalRead(pinInst2);
    FFInst3[0] = digitalRead(pinInst3);
    FFInst4[0] = digitalRead(pinInst4);
    InstOn1 = !FFInst1[1] && FFInst1[0];
    InstOn2 = !FFInst1[1] && FFInst1[0];
    InstOn3 = !FFInst1[1] && FFInst1[0];
    InstOn4 = !FFInst1[1] && FFInst1[0];
    
    //Change State
    //録音開始
    if(digitalRead(pinRecordStart)  == HIGH) curRecord = S_RECORD_START;
    //終了
    if( (curRecord = S_RECORD_START && digitalRead(pinRecordStop) == HIGH) || error  ) curRecord = S_RECORD_IDLE;
    //再生開始
    if(curRecord == S_RECORD_IDLE && digitalRead(pinPlayStart) == HIGH) curPlay = S_PLAY_START;
    //再生停止
    if(digitalRead(pinPlayStop) == HIGH || curRecord = S_RECORD_START || error) curPlay = S_PLAY_IDLE;

    //State -> Signal
    if(curRecord == S_RECORD_IDLE){
        cntRecordInst1 = 0;
        cntRecordInst2 = 0;
        cntRecordInst3 = 0;
        cntRecordInst4 = 0;
        iterRecordInst1 = 0;
        iterRecordInst2 = 0;
        iterRecordInst3 = 0;
        iterRecordInst4 = 0;
    }
    if(curPlay == S_PLAY_IDLE){
        cntPlayInst1 = 0;
        cntPlayInst2 = 0;
        cntPlayInst3 = 0;
        cntPlayInst4 = 0;
        iterPlayInst1 = 0;
        iterPlayInst2 = 0;
        iterPlayInst3 = 0;
        iterPlayInst4 = 0;
    }
    if(curRecord == S_RECORD_START){
        //待ち時間を格納
        if(InstOn1){
            loopInst1[iterPlayInst1] = cntRecordInst1;
            cntRecordInst1 = 0;
            iterRecordInst1++;
        }
        //待ち時間++
        else cntRecordInst1++;

        if(InstOn2){
            loopInst2[iterRecordInst2] = cntRecordInst2;
            cntRecordInst2 = 0;
            iterRecordInst2++;
        }
        else cntRecordInst2++;

        if(InstOn3){
            loopInst3[iterRecordInst3] = cntRecordInst3;
            cntRecordInst3 = 0;
            iterRecordInst3++;
        }
        else cntRecordInst3++;

        if(InstOn4){
            loopInst4[iterRecordInst4] = cntRecordInst4;
            cntRecordInst4 = 0;
            iterRecordInst4++;
        }
        else cntRecordInst4++;
    }
    if(curPlay == S_PLAY_START) {
        //待ち時間を格納
        if(loopInst1[iterPlayInst1] = cntPlayInst1){
            loopInst1[iterPlayInst1] = cntPlayInst1;
            cntPlayInst1 = 0;
            if(iterPlayInst1 != MAX_SIZE -1) iterPlayInst1++;
            else iterPlayInst1 = 0;
            //鳴らす
        }
        //待ち時間++
        else {
            if(cntPlayInst1 != )
            cntPlayInst1++;
        }
        if(InstOn2){
            loopInst2[iterPlayInst2] = cntPlayInst2;
            cntPlayInst2 = 0;
            iterPlayInst2++;
        }
        else cntPlayInst2++;
        if(InstOn3){
            loopInst3[iterPlayInst3] = cntPlayInst3;
            cntPlayInst3 = 0;
            iterPlayInst3++;
        }
        else cntPlayInst3++;
        if(InstOn4){
            loopInst4[iterPlayInst4] = cntPlayInst4;
            cntPlayInst4 = 0;
            iterPlayInst4++;
        }
        else cntPlayInst4++;
    }
}
