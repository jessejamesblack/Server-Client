PORT = 8080
HOST = vi.cs.rutgers.edu 
make default:
	gcc -g -Wall -pthread -lm sorter_client.c -o sorter_client
	gcc -g -Wall -pthread -lm sorter_server.c -o sorter_server
	
client:
	gcc -g -pthread -lm sorter_client.c -o sorter_client
	
server:
	gcc -g -pthread -lm sorter_server.c -o sorter_server

test:
	./sorter_client -c color -h $(HOST) -p $(PORT)
	./sorter_client -c director_name -h $(HOST) -p $(PORT)
	./sorter_client -c num_critic_for_reviews -h $(HOST) -p $(PORT)
	./sorter_client -c duration -h $(HOST) -p $(PORT)
	./sorter_client -c director_facebook_likes -h $(HOST) -p $(PORT)
	./sorter_client -c actor_3_facebook_likes -h $(HOST) -p $(PORT)
	./sorter_client -c actor_2_name -h $(HOST) -p $(PORT)
	./sorter_client -c actor_1_facebook_likes -h $(HOST) -p $(PORT)
	./sorter_client -c movie_title -h $(HOST) -p $(PORT)
	./sorter_client -c num_voted_users -h $(HOST) -p $(PORT)
	./sorter_client -c cast_total_facebook_likes -h $(HOST) -p $(PORT)
	./sorter_client -c actor_3_name -h $(HOST) -p $(PORT)
	./sorter_client -c facenumber_in_poster -h $(HOST) -p $(PORT)
	./sorter_client -c plot_keywords -h $(HOST) -p $(PORT)
	./sorter_client -c movie_imdb_link -h $(HOST) -p $(PORT)
	./sorter_client -c num_user_for_reviews -h $(HOST) -p $(PORT)
	./sorter_client -c language -h $(HOST) -p $(PORT)
	./sorter_client -c country -h $(HOST) -p $(PORT)
	./sorter_client -c content_rating -h $(HOST) -p $(PORT)
	./sorter_client -c budget -h $(HOST) -p $(PORT)
	./sorter_client -c title_year -h $(HOST) -p $(PORT)
	./sorter_client -c actor_2_facebook_likes -h $(HOST) -p $(PORT)
	./sorter_client -c imdb_score -h $(HOST) -p $(PORT)
	./sorter_client -c aspect_ratio -h $(HOST) -p $(PORT)
	./sorter_client -c movie_facebook_likes -h $(HOST) -p $(PORT)
	
