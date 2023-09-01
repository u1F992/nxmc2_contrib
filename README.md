# nxmc2_contrib

## Overview

The `nxmc2_contrib` library provides a straightforward way to build and execute commands conforming to the [NX Macro Controller v2](https://blog.bzl-web.com/entry/2020/01/20/165719) protocol[^1].

It includes the functionality for parsing raw byte sequences into structured command objects and subsequently executing these commands through a extensible executor. This makes it easy to develop NXMC2-compatible devices or software.

Written in the C programming language, this library is highly portable, making it easy to adapt across a variety of platforms.

[^1]: https://scrapbox.io/yatsuna827827-12010999/Nintendo_Switch%E3%82%92%E6%93%8D%E4%BD%9C%E3%81%99%E3%82%8B%E3%83%97%E3%83%AD%E3%82%B0%E3%83%A9%E3%83%A0%E3%81%AE%E4%BB%95%E6%A7%98%E3%82%92%E8%AA%BF%E3%81%B9%E3%82%8B

## Example

```c
#include <assert.h>

#include "nxmc2_command.h"

static nxmc2_command_button_t y_state;
static void y(nxmc2_command_button_t state)
{
    y_state = state;
}

int main(void)
{
    uint8_t test[] = {0xABU, 1U, 0U, 8U, 126U, 127U, 128U, 129U, 0xFFU, 0xFEU, 0xFDU};
    nxmc2_command_t command;

    nxmc2_command_builder_t builder;
    nxmc2_command_builder_init(&builder);

    nxmc2_command_executor_t executor;
    nxmc2_command_executor_init(&executor);
    executor.y = y;

    for (int i = 0; i < 11; i++)
    {
        assert(nxmc2_command_builder_append(&builder, test[i]));
    }

    assert(nxmc2_command_builder_build(&builder, &command));
    nxmc2_command_executor_exec(&executor, &command);
    assert(y_state == NXMC2_COMMAND_BUTTON_PRESSED);
}
```