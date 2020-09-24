#pragma once

#include <stdbool.h>

int abnf_parser_add_ruleset(const char* filename);

bool abnf_parser_matchrule(const char* expression, const char* rule);
