#include <cs50.h>
#include <stdio.h>
#include <strings.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void mergesort(pair merge_pairs[], int s, int e);
int pair_strength(pair temp_array[], int ls_rs);
bool check_cycle(int winner, int loser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    // initialize all preferences to 0
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            preferences[i][j] = 0;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if ((strcasecmp(name, candidates[i])) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if ((preferences[i][j] - preferences[j][i]) > 0)
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
                continue;
            }
            if ((preferences[i][j] - preferences[j][i]) < 0)
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
                continue;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    // s stands for index of start point of the pairs[], e in other way stands for the end
    int s = 0, e = pair_count - 1;
    mergesort(pairs, s, e);
    return;
}

void mergesort(pair merge_pairs[], int s, int e)
{
    if (s == e)
    {
        return;
    }
    int mid = (s + e) / 2;
    mergesort(merge_pairs, s, mid);
    mergesort(merge_pairs, mid + 1, e);
    pair temp_array[e - s + 1];
    for (int i = 0, j = s; i < e - s + 1; i++, j++)
    {
        temp_array[i] = merge_pairs[j];
    }
    for (int i = 0, j = s, ls = 0, rs = (mid + 1) - s; i < e - s + 1; i++)
    {
        if (ls > (e - s) / 2)
        {
            while (rs <= (e - s))
            {
                merge_pairs[j] = temp_array[rs];
                rs++, j++;
            }
            return;
        }
        if (rs > (e - s))
        {
            while (ls <= (e - s) / 2)
            {
                merge_pairs[j] = temp_array[ls];
                ls++, j++;
            }
            return;
        }
        if (pair_strength(temp_array, ls) > pair_strength(temp_array, rs))
        {
            merge_pairs[j] = temp_array[ls];
            ls++, j++;
        }
        else if (pair_strength(temp_array, ls) < pair_strength(temp_array, rs))
        {
            merge_pairs[j] = temp_array[rs];
            rs++, j++;
        }
        else
        {
            merge_pairs[j] = temp_array[ls];
            j++;
            merge_pairs[j] = merge_pairs[j - 1];
            j++, i++, ls++, rs++;
        }
    }
}

int pair_strength(pair temp_array[], int ls_rs)
{
    return preferences[temp_array[ls_rs].winner][temp_array[ls_rs].loser] -
           preferences[temp_array[ls_rs].loser][temp_array[ls_rs].winner];
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        // check if addding pairs[i]'s edge would create a cycle, if so, skip the edge, if not,
        // locked[winner][loser] = true, locked[pairs[i].winner][pairs[i].loser]
        if ((i == 0) || (i == 1))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
            continue;
        }
        if (!check_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

bool check_cycle(int winner, int loser)
{
    if (locked[loser][winner])
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][winner])
        {
            return check_cycle(i, loser);
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                break;
            }
            if (j == (candidate_count - 1))
            {
                printf("%s\n", candidates[i]);
            }
        }
    }
    return;
}
