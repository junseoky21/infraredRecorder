/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: junse
 *
 * Created on April 20, 2019, 11:59 PM
 */


#include "InfraredIO.h"
#include <argp.h>


const char *argpProgramVersion = "RaspInfraredTool";
const char *argpProgramBugAddress = "junseoky21@gmail.com";
static char doc[] = "RaspberryPI tool to receive and send infrared signals to control IR devices";
static char argsDoc[] = "[pinnum]...";
static struct argp_option options[] = {
    {"receive",     'r', 0,             0, "Wait for receive signal"},
    {"transmit",    't', "filename",    0, "Read the stored signal file and transmit the signal"},
    {"output",      'o', "filename",    0, "Specifies the output path for the received signal"},
    {"verbose",     'v', 0,             0, "Prints out ongoing activities verbosely at the stdout"},
    { 0 }
};

struct arguments {
    int verbose, receive, transmit, pinnum;
    char *outputWriteFile;
    char *transmitReadFile;
};

static error_t parseOpt(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = state->input;
    switch (key) {
        case 'r': 
            arguments->receive = 1;
            break;
        case 't': 
            arguments->transmit = 1;
            arguments->transmitReadFile = arg;
            break;
        case 'o': 
            arguments->outputWriteFile = arg;
            break;
        case 'v': 
            arguments->verbose = 1;
            break;
        case ARGP_KEY_ARG:
            arguments->pinnum = atoi(arg);
            return 0;
        default: return ARGP_ERR_UNKNOWN;
    }   
    return 0;
}

static struct argp argp = { options, parseOpt, argsDoc, doc, 0, 0, 0 };


/*
 * main entry point here
 */
int main(int argc, char** argv) {
    struct arguments arguments;
    arguments.outputWriteFile = NULL;
    arguments.transmitReadFile = NULL;
    arguments.verbose = 0;
    arguments.transmit = 0;
    arguments.receive = 0;
    arguments.pinnum = -1;
    
    argp_parse(&argp, argc, argv, 0, 0, &arguments);
    printf("Arguments received %s, %s, %d, %d, %d, %d\n",
            arguments.outputWriteFile,
            arguments.transmitReadFile,
            arguments.verbose,
            arguments.transmit,
            arguments.receive,
            arguments.pinnum
    );
    if (arguments.receive) {
        FILE *outFP = NULL;
        int mask = 0;
        if (arguments.outputWriteFile) {
            outFP = fopen(arguments.outputWriteFile, "w");
            mask |= INFRA_RECV_FILE;
        }
        if (arguments.verbose) {
            mask |= INFRA_RECV_PRINT;
        }
        InfraredReceive(arguments.pinnum, 1, mask, outFP);
    }
    else if (arguments.transmit) {
        
    }
    return (EXIT_SUCCESS);
}

