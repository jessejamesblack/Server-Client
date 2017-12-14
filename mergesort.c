#include "sorter_server.h"

void mymergesort(struct Tokenizer **arr, int size, char *columnName)
{
    int idx;
    struct Tokenizer **temp;

    if (size < 2)
        return;

    mymergesort(arr, size / 2, columnName);
    mymergesort(arr + (size / 2), size - (size / 2), columnName);

    temp = malloc(size * sizeof *temp);
    mymerge(arr, size / 2, arr + (size / 2), size - (size / 2), temp, columnName);
    for (idx = 0; idx < size; idx++)
        arr[idx] = temp[idx];
    free(temp);
}


void mymerge(struct Tokenizer **arr1, int size1, struct Tokenizer **arr2, int size2, struct Tokenizer **arr3, char *columnName)
{

    int read1, read2, writeind;

    for (read1 = read2 = writeind = 0; read1 < size1 && read2 < size2;)
    {
        if (strcmp(columnName, "imdb_score") == 0)
        {
            if (arr1[read1]->imdb_score < arr2[read2]->imdb_score)
            {
                arr3[writeind++] = arr1[read1++];
            }
            else
            {
                arr3[writeind++] = arr2[read2++];
            }
        }
        if (strcmp(columnName, "aspect_ratio") == 0)
        {
            if (arr1[read1]->aspect_ratio < arr2[read2]->aspect_ratio)
            {
                arr3[writeind++] = arr1[read1++];
            }
            else
            {
                arr3[writeind++] = arr2[read2++];
            }
        }
        if (strcmp(columnName, "num_critic_for_reviews") == 0)
        {
            if (arr1[read1]->num_critic_for_reviews < arr2[read2]->num_critic_for_reviews)
            {
                arr3[writeind++] = arr1[read1++];
            }
            else
            {
                arr3[writeind++] = arr2[read2++];
            }
        }
        if (strcmp(columnName, "duration") == 0)
        {
            if (arr1[read1]->duration < arr2[read2]->duration)
            {
                arr3[writeind++] = arr1[read1++];
            }
            else
            {
                arr3[writeind++] = arr2[read2++];
            }
        }
        if (strcmp(columnName, "director_facebook_likes") == 0)
        {
            if (arr1[read1]->director_facebook_likes < arr2[read2]->director_facebook_likes)
            {
                arr3[writeind++] = arr1[read1++];
            }
            else
            {
                arr3[writeind++] = arr2[read2++];
            }
        }
        if (strcmp(columnName, "actor_3_facebook_likes") == 0)
        {
            if (arr1[read1]->actor_3_facebook_likes < arr2[read2]->actor_3_facebook_likes)
            {
                arr3[writeind++] = arr1[read1++];
            }
            else
            {
                arr3[writeind++] = arr2[read2++];
            }
        }
        if (strcmp(columnName, "actor_1_facebook_likes") == 0)
        {
            if (arr1[read1]->actor_1_facebook_likes < arr2[read2]->actor_1_facebook_likes)
            {
                arr3[writeind++] = arr1[read1++];
            }
            else
            {
                arr3[writeind++] = arr2[read2++];
            }
        }
        if (strcmp(columnName, "gross") == 0)
        {
            if (arr1[read1]->gross < arr2[read2]->gross)
            {
                arr3[writeind++] = arr1[read1++];
            }
            else
            {
                arr3[writeind++] = arr2[read2++];
            }
        }
        if (strcmp(columnName, "num_voted_users") == 0)
        {
            if (arr1[read1]->num_voted_users < arr2[read2]->num_voted_users)
            {
                arr3[writeind++] = arr1[read1++];
            }
            else
            {
                arr3[writeind++] = arr2[read2++];
            }
        }
        if (strcmp(columnName, "cast_total_facebook_likes") == 0)
        {
            if (arr1[read1]->cast_total_facebook_likes < arr2[read2]->cast_total_facebook_likes)
            {
                arr3[writeind++] = arr1[read1++];
            }
            else
            {
                arr3[writeind++] = arr2[read2++];
            }
        }
        if (strcmp(columnName, "facenumber_in_poster") == 0)
        {
            if (arr1[read1]->facenumber_in_poster < arr2[read2]->facenumber_in_poster)
            {
                arr3[writeind++] = arr1[read1++];
            }
            else
            {
                arr3[writeind++] = arr2[read2++];
            }
        }
        if (strcmp(columnName, "num_user_for_reviews") == 0)
        {
            if (arr1[read1]->num_user_for_reviews < arr2[read2]->num_user_for_reviews)
            {
                arr3[writeind++] = arr1[read1++];
            }
            else
            {
                arr3[writeind++] = arr2[read2++];
            }
        }
        if (strcmp(columnName, "budget") == 0)
        {
            if (arr1[read1]->budget < arr2[read2]->budget)
            {
                arr3[writeind++] = arr1[read1++];
            }
            else
            {
                arr3[writeind++] = arr2[read2++];
            }
        }
        if (strcmp(columnName, "title_year") == 0)
        {
            if (arr1[read1]->title_year < arr2[read2]->title_year)
            {
                arr3[writeind++] = arr1[read1++];
            }
            else
            {
                arr3[writeind++] = arr2[read2++];
            }
        }
        if (strcmp(columnName, "actor_2_facebook_likes") == 0)
        {
            if (arr1[read1]->actor_2_facebook_likes < arr2[read2]->actor_2_facebook_likes)
            {
                arr3[writeind++] = arr1[read1++];
            }
            else
            {
                arr3[writeind++] = arr2[read2++];
            }
        }
        if (strcmp(columnName, "movie_facebook_likes") == 0)
        {
            if (arr1[read1]->movie_facebook_likes < arr2[read2]->movie_facebook_likes)
            {
                arr3[writeind++] = arr1[read1++];
            }
            else
            {
                arr3[writeind++] = arr2[read2++];
            }
        }
        if (strcmp(columnName, "color") == 0)
        {
            if (strcmp(arr1[read1]->color, arr2[read2]->color) <= 0)
            {
                arr3[writeind++] = arr1[read1++];
            }
            else
            {
                arr3[writeind++] = arr2[read2++];
            }
        }
        if (strcmp(columnName, "director_name") == 0)
        {
            if (strcmp(arr1[read1]->director_name, arr2[read2]->director_name) <= 0)
            {
                arr3[writeind++] = arr1[read1++];
            }
            else
            {
                arr3[writeind++] = arr2[read2++];
            }
        }
        if (strcmp(columnName, "actor_2_name") == 0)
        {
            if (strcmp(arr1[read1]->actor_2_name, arr2[read2]->actor_2_name) <= 0)
            {
                arr3[writeind++] = arr1[read1++];
            }
            else
            {
                arr3[writeind++] = arr2[read2++];
            }
        }
        if (strcmp(columnName, "genres") == 0)
        {
            if (strcmp(arr1[read1]->genres, arr2[read2]->genres) <= 0)
            {
                arr3[writeind++] = arr1[read1++];
            }
            else
            {
                arr3[writeind++] = arr2[read2++];
            }
        }
        if (strcmp(columnName, "actor_1_name") == 0)
        {
            if (strcmp(arr1[read1]->actor_1_name, arr2[read2]->actor_1_name) <= 0)
            {
                arr3[writeind++] = arr1[read1++];
            }
            else
            {
                arr3[writeind++] = arr2[read2++];
            }
        }
        if (strcmp(columnName, "movie_title") == 0)
        {
            if (strcmp(arr1[read1]->movie_title, arr2[read2]->movie_title) <= 0)
            {
                arr3[writeind++] = arr1[read1++];
            }
            else
            {
                arr3[writeind++] = arr2[read2++];
            }
        }
        if (strcmp(columnName, "actor_3_name") == 0)
        {
            if (strcmp(arr1[read1]->actor_3_name, arr2[read2]->actor_3_name) <= 0)
            {
                arr3[writeind++] = arr1[read1++];
            }
            else
            {
                arr3[writeind++] = arr2[read2++];
            }
        }
        if (strcmp(columnName, "plot_keywords") == 0)
        {
            if (strcmp(arr1[read1]->plot_keywords, arr2[read2]->plot_keywords) <= 0)
            {
                arr3[writeind++] = arr1[read1++];
            }
            else
            {
                arr3[writeind++] = arr2[read2++];
            }
        }
        if (strcmp(columnName, "movie_imdb_link") == 0)
        {
            if (strcmp(arr1[read1]->movie_imdb_link, arr2[read2]->movie_imdb_link) <= 0)
            {
                arr3[writeind++] = arr1[read1++];
            }
            else
            {
                arr3[writeind++] = arr2[read2++];
            }
        }
        if (strcmp(columnName, "language") == 0)
        {
            if (strcmp(arr1[read1]->language, arr2[read2]->language) <= 0)
            {
                arr3[writeind++] = arr1[read1++];
            }
            else
            {
                arr3[writeind++] = arr2[read2++];
            }
        }
        if (strcmp(columnName, "country") == 0)
        {
            if (strcmp(arr1[read1]->country, arr2[read2]->country) <= 0)
            {
                arr3[writeind++] = arr1[read1++];
            }
            else
            {
                arr3[writeind++] = arr2[read2++];
            }
        }
        if (strcmp(columnName, "content_rating") == 0)
        {
            if (strcmp(arr1[read1]->content_rating, arr2[read2]->content_rating) <= 0)
            {
                arr3[writeind++] = arr1[read1++];
            }
            else
            {
                arr3[writeind++] = arr2[read2++];
            }
        }
    }

    while (read1 < size1)
        arr3[writeind++] = arr1[read1++];

    while (read2 < size2)
        arr3[writeind++] = arr2[read2++];
}
