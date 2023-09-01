#ifndef NXMC2_CONTRIB_H_
#define NXMC2_CONTRIB_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

extern const uint8_t NXMC2_COMMAND_HEADER;

typedef enum
{
    NXMC2_COMMAND_BUTTON_STATE_RELEASED,
    NXMC2_COMMAND_BUTTON_STATE_PRESSED
} NXMC2CommandButtonState;

typedef enum
{
    NXMC2_COMMAND_HAT_STATE_UP,
    NXMC2_COMMAND_HAT_STATE_UPRIGHT,
    NXMC2_COMMAND_HAT_STATE_RIGHT,
    NXMC2_COMMAND_HAT_STATE_DOWNRIGHT,
    NXMC2_COMMAND_HAT_STATE_DOWN,
    NXMC2_COMMAND_HAT_STATE_DOWNLEFT,
    NXMC2_COMMAND_HAT_STATE_LEFT,
    NXMC2_COMMAND_HAT_STATE_UPLEFT,
    NXMC2_COMMAND_HAT_STATE_NEUTRAL
} NXMC2CommandHatState;

extern const uint8_t NXMC2_COMMAND_STICK_NEUTRAL;

typedef struct NXMC2Command
{
    uint8_t header;

    NXMC2CommandButtonState y;
    NXMC2CommandButtonState b;
    NXMC2CommandButtonState a;
    NXMC2CommandButtonState x;
    NXMC2CommandButtonState l;
    NXMC2CommandButtonState r;
    NXMC2CommandButtonState zl;
    NXMC2CommandButtonState zr;

    NXMC2CommandButtonState minus;
    NXMC2CommandButtonState plus;
    NXMC2CommandButtonState l_click;
    NXMC2CommandButtonState r_click;
    NXMC2CommandButtonState home;
    NXMC2CommandButtonState capture;
    uint8_t _;

    NXMC2CommandHatState hat;
    uint8_t lx;
    uint8_t ly;
    uint8_t rx;
    uint8_t ry;

    uint8_t ext0;
    uint8_t ext1;
    uint8_t ext2;
} NXMC2Command;

typedef struct NXMC2CommandBuilder
{
    uint8_t raw_[11];
    size_t ptr_;
} NXMC2CommandBuilder;

typedef struct NXMC2CommandHandlers
{
    void (*y)(NXMC2CommandButtonState state);
    void (*b)(NXMC2CommandButtonState state);
    void (*a)(NXMC2CommandButtonState state);
    void (*x)(NXMC2CommandButtonState state);
    void (*l)(NXMC2CommandButtonState state);
    void (*r)(NXMC2CommandButtonState state);
    void (*zl)(NXMC2CommandButtonState state);
    void (*zr)(NXMC2CommandButtonState state);
    void (*minus)(NXMC2CommandButtonState state);
    void (*plus)(NXMC2CommandButtonState state);
    void (*l_click)(NXMC2CommandButtonState state);
    void (*r_click)(NXMC2CommandButtonState state);
    void (*home)(NXMC2CommandButtonState state);
    void (*capture)(NXMC2CommandButtonState state);
    void (*hat)(NXMC2CommandHatState state);
    void (*l_stick)(uint8_t x, uint8_t y);
    void (*r_stick)(uint8_t x, uint8_t y);
    void (*ext)(uint8_t ext0, uint8_t ext1, uint8_t ext2);
} NXMC2CommandHandlers;

void nxmc2_command_builder_clear(NXMC2CommandBuilder *builder);
void nxmc2_command_builder_append(NXMC2CommandBuilder *builder, uint8_t packet);
bool nxmc2_command_builder_build(NXMC2CommandBuilder *builder, NXMC2Command *command);
void nxmc2_command_builder_initialize(NXMC2CommandBuilder *builder);
void nxmc2_command_execute(NXMC2Command *command, NXMC2CommandHandlers *handlers);
void nxmc2_command_handlers_initialize(NXMC2CommandHandlers *handlers);

#endif