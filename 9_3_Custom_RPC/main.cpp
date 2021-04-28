#include "mbed.h"
#include "mbed_rpc.h"

/**
 *  This example program has been updated to use the RPC implementation in the new mbed libraries.
 *  This example demonstrates using RPC over serial
**/
RpcDigitalOut myled1(LED1,"myled1");
RpcDigitalOut myled2(LED2,"myled2");
RpcDigitalOut myled3(LED3,"myled3");
BufferedSerial pc(USBTX, USBRX);
void LEDControl(Arguments *in, Reply *out);
void LEDSwitch(Arguments *in, Reply *out);
RPCFunction rpcLED(&LEDControl, "LEDControl");
RPCFunction rpcLED1(&LEDSwitch, "LEDSwitch");
double x, y;

int main() {
    //The mbed RPC classes are now wrapped to create an RPC enabled version - see RpcClasses.h so don't add to base class
    // receive commands, and send back the responses
    char buf[256], outbuf[512];

    FILE *devin = fdopen(&pc, "r");
    FILE *devout = fdopen(&pc, "w");

    while(1) {
        memset(buf, 0, 256);
        for (int i = 0; ; i++) {
            char recv = fgetc(devin);
            if (recv == '\n') {
                printf("\r\n");
                break;
            }
            buf[i] = fputc(recv, devout);
        }
        //Call the static call method on the RPC class
        RPC::call(buf, outbuf);
        printf("%s\r\n", outbuf);
    }
}

// Make sure the method takes in Arguments and Reply objects.
void LEDControl (Arguments *in, Reply *out)   {
    bool success = true;

    // In this scenario, when using RPC delimit the two arguments with a space.
    x = in->getArg<double>();
    y = in->getArg<double>();

    // Have code here to call another RPC function to wake up specific led or close it.
    char buffer[200], outbuf[256];
    char strings[20];
    int led = x;
    int on = y;
    sprintf(strings, "/myled%d/write %d", led, on);
    strcpy(buffer, strings);
    RPC::call(buffer, outbuf);
    if (success) {
        out->putData(buffer);
    } else {
        out->putData("Failed to execute LED control.");
    }
}

void LEDSwitch(Arguments *in, Reply *out)
{
    bool success = true;

    // In this scenario, when using RPC delimit the one argument with a space.
    x = in->getArg<double>();

    // Have code here to call another RPC function to wake up specific led or close it.
    char buffer[300], outbuf[512];
    char strings[20];
    int onSwitch;
    int i = 0;
    if (x != 0) onSwitch = 1;

    while (onSwitch == 1 && recv == 0) {
        printf("execute on= %d \n", onSwitch);
        /*sprintf(strings, "/myled1/write 1");
        strcpy(buffer, strings);
        RPC::call(buffer, outbuf);
        if (success) {
            out->putData(buffer);
        } else {
            out->putData("Failed to execute LED control.");
        }
        ThisThread::sleep_for(100ms);
        sprintf(strings, "/myled1/write 0");
        strcpy(buffer, strings);
        RPC::call(buffer, outbuf);
        if (success) {
            out->putData(buffer);
        } else {
            out->putData("Failed to execute LED control.");
        }
        ThisThread::sleep_for(100ms);
        */
        sprintf(strings, "/myled3/write 1");
        strcpy(buffer, strings);
        RPC::call(buffer, outbuf);
        /*if (success) {
            out->putData(buffer);
        } else {
            out->putData("Failed to execute LED control.");
        }*/
        ThisThread::sleep_for(100ms);
        sprintf(strings, "/myled3/write 0");
        strcpy(buffer, strings);
        RPC::call(buffer, outbuf);
        /*if (success) {
            out->putData(buffer);
        } else {
            out->putData("Failed to execute LED control.");
        }*/
        ThisThread::sleep_for(100ms);
        i++;
        if (i == 20) onSwitch = 0;

    }
/*
    sprintf(strings, "/myled%d/write %d", led, on);
    strcpy(buffer, strings);
    RPC::call(buffer, outbuf);
    
    if (success) {
        out->putData(buffer);
    } else {
        out->putData("Failed to execute LED control.");
    }
*/
}
