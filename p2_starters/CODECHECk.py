#!/usr/bin/python3

import os
import argparse
from pprint import pprint

import clang.check
import clang.tidy
import clang.format


def main(project_dir, silent=False):
    # Formatting initialization
    files = ['server_type.h', 'simulation.cpp', 'p2.cpp', 'simulation.h']
    format_dir = os.path.join(project_dir, 'formatted')
    simulation_cpp_files = ['simulation.cpp', 'simulation.h']
    main_cpp_name = 'p2.cpp'
    main_cpp_path = os.path.join(project_dir, main_cpp_name)

    # Clang checkings
    clang.format.generate_formatted_files(project_dir, format_dir, files, silent=silent)
    clang_check_score = 0
    subroutine_count = 0
    long_function_count = 0
    uncomment_prototype_cnt = 0
    poorly_commented_cnt = 0

    # Checkpoint 1: Main function length
    # Requirement: Main function should be no longer than 50 physical lines.
    main_function = clang.check.parse_functions(main_cpp_name, main_cpp_path, silent=silent)
    for func_prototype, func in main_function.items():
        if func.func_declarations[0].end - func.func_declarations[0].start >= 50:
            long_function_count += 1

    functions = clang.check.parse_functions_new(format_dir, simulation_cpp_files, silent=silent)
    clang.check.parse_comments(functions, silent=silent)
    for func_prototype, func in functions.items():
        # Checkpoint 2: Non-main function amount
        # Requirement: Program should be split into at least 10 non-main functions.
        if func.name != 'main' and func.len >= 1:
            subroutine_count += 1

        # Checkpoint 3: Non-main function length and amount
        # Requirement: Non-main functions should be no longer than 150 physical lines.
        if func.name != 'main' and func.len >= 150:
            long_function_count += 1

        # Checkpoint 4: Function declaration comments (REQUIRES, MODIFIES, EFFECTS)
        # Requirement: All functions should have RME in their declaration.
        if func.prototype_comments == 0:
            uncomment_prototype_cnt += 1

        # Checkpoint 5: Function body comments
        # Requirement: the length of function // the number of comments < 50.
        if func.body_comments == 0:
            if func.len >= 50:
                poorly_commented_cnt += 1
        elif func.len // func.body_comments >= 50:
            poorly_commented_cnt += 1

    clang_check_score += min(2, subroutine_count // 5)
    clang_check_score += max(0, 2 - long_function_count)
    clang_check_score += max(0, 3 - uncomment_prototype_cnt)
    clang_check_score += max(0, 3 - poorly_commented_cnt)
    clang_check_score //= 2

    if not silent:
        print('\nsubroutines: %d, \nlong functions: %d, \nuncomment declarations: %d, \npoorly commented functions: %d'
              % (subroutine_count, long_function_count, uncomment_prototype_cnt, poorly_commented_cnt))
        print('clang-check score: %d' % clang_check_score)

    clang_tidy_warnings, clang_tidy_warnings_count = clang.tidy.parse_warnings_new(project_dir, files, silent=silent)
    clang_tidy_score = 0

    # Checkpoint 6: Clang tidies
    # Requirement: Your program should be free of clang tidies.
    if clang_tidy_warnings_count <= 5:
        clang_tidy_score += 3
    elif clang_tidy_warnings_count <= 10:
        clang_tidy_score += 2
    elif clang_tidy_warnings_count <= 25:
        clang_tidy_score += 1

    if len(clang_tidy_warnings) <= 2:
        clang_tidy_score += 2
    elif len(clang_tidy_warnings) <= 5:
        clang_tidy_score += 1
    if not silent:
        pprint(clang_tidy_warnings)
        print('\nclang-tidy score: %d' % clang_tidy_score)
        print('\nTotal style score: %d' % (clang_tidy_score + clang_check_score))

    if silent:
        print('%d,%d' % (clang_check_score, clang_tidy_score))


parser = argparse.ArgumentParser(description='Project 2 Code Checker.')
parser.add_argument('--silent', action='store_true')
parser.add_argument('project_dir', type=str, nargs=1)
args = parser.parse_args()
main(args.project_dir[0], silent=args.silent)