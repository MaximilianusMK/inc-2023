# INC 2023 - Problem Repository

## Repository Structure

Each problem (from PA to PD for trial and A to M for contest) has their own folder. The folder name is the `slug` of the problem, which is the codename we used when we internally prepare the problems. The following table describes the slug for each problem

| Problem Code | Problem Slug | Problem Title         |
| ------------ | ------------ | --------------------- |
| PA           | party        | Party Medley          |
| PB           | steak        | Cooking Steaks        |
| PC           | stock        | Stock Market          |
| PD           | power        | Powers of Two         |
| A            | gold         | Golden Tickets        |
| B            | diet         | Diet Plan             |
| C            | max          | Independent Set (Max) |
| D            | sum          | Independent Set (Min) |
| E            | reverse      | Reverse Severer       |
| F            | privacy      | Interesting Couple    |
| G            | narrow       | Narrow Passageway     |
| H            | horse        | Horse Carts           |
| I            | critical     | Critical Roads        |
| J            | pairs        | Counting Pairs        |
| K            | square       | Magic Squares         |
| L            | numbers      | Numbers Combination   |
| M            | choco        | Chocolate Bar         |

In the problem folder, there should be exactly the following file/folder:

- `description.pdf`. The problem statement distributed to the contestants during the contest.
- `data/`. A folder consisting of all testcases. The sample inputs given in the problem statement will be in the form of `sample/icpc-<slug>_sample_<testcase number>.in/ans`, while the hidden testcases will be in the form of `secret/icpc-<slug>_1_<testcase number>.in/ans`.
- `solution.cpp`. The official solution used to generate the outputs of the testcases
- `scorer.cpp`. A validator used to validate contestants' output. The code accepts three arguments.
  - The first parameter will be used as the filename of the input file
  - The second parameter will be used as the filename of the judge's output file
  - The third parameter will be used as the filename of the contestant's output file
  - This code will print `WA` to stdout if the contestant's output is intended to be judged `WRONG ANSWER`, while it will print `AC` to stdout if the contestants's output is intended to be judged `CORRECT`.
- `verifier.py`. A verifier used to validate the input of the testcases. The code will crash if the input violates the problem constraint, while it will exit gracefully and will not output anything if the input satisfies the problem constraint.

## Limitations

The following table describes the time limit for each problem, as broadcasted to all teams at the beginning of the contest:

| Problem Code | Problem Slug | Time Limit |
| ------------ | ------------ | ---------- |
| PA           | party        | 1 sec      |
| PB           | steak        | 1 sec      |
| PC           | stock        | 1 sec      |
| PD           | power        | 1 sec      |
| A            | gold         | 1 sec      |
| B            | diet         | 1 sec      |
| C            | max          | 1 sec      |
| D            | sum          | 1 sec      |
| E            | reverse      | 1 sec      |
| F            | privacy      | 2 sec      |
| G            | narrow       | 1 sec      |
| H            | horse        | 1 sec      |
| I            | critical     | 1 sec      |
| J            | pairs        | 1 sec      |
| K            | square       | 1 sec      |
| L            | numbers      | 2 sec      |
| M            | choco        | 1 sec      |

The memory limit for all problems is 256MB, as broadcasted to all teams at the beginning of the contest.

## Solutions

Note that while there is only one official published solution, we have a lot of other solutions prepared for our internal testing. These other solutions include, but not limited to:

- Solutions in several other languages
- Solutions that is intended to be incorrect (e.g. WA, TLE, etc.)
- Other correct solutions (especially on problems with more than one correct outputs for each input)

## Errata

None.

## Additional Notes

The problemset was officially deployed by the judges on [TLX](https://tlx.toki.id/problems/inc-2023).