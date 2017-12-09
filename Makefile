PORT = 8080
HOST = vi.cs.rutgers.edu 
make default:
	gcc -g -Wall -pthread -lm client.c -o client
	gcc -g -Wall -pthread -lm server.c -o server
	
client:
	gcc -g -pthread -lm client.c -o client
	
server:
	gcc -g -pthread -lm server.c -o servers

test:
	./client -c color -h $(HOST) -p $(PORT)
	./client -c director_name -h $(HOST) -p $(PORT)
	./client -c num_critic_for_reviews -h $(HOST) -p $(PORT)
	./client -c duration -h $(HOST) -p $(PORT)
	./client -c director_facebook_likes -h $(HOST) -p $(PORT)
	./client -c actor_3_facebook_likes -h $(HOST) -p $(PORT)
	./client -c actor_2_name -h $(HOST) -p $(PORT)
	./client -c actor_1_facebook_likes -h $(HOST) -p $(PORT)
	./client -c movie_title -h $(HOST) -p $(PORT)
	./client -c num_voted_users -h $(HOST) -p $(PORT)
	./client -c cast_total_facebook_likes -h $(HOST) -p $(PORT)
	./client -c actor_3_name -h $(HOST) -p $(PORT)
	./client -c facenumber_in_poster -h $(HOST) -p $(PORT)
	./client -c plot_keywords -h $(HOST) -p $(PORT)
	./client -c movie_imdb_link -h $(HOST) -p $(PORT)
	./client -c num_user_for_reviews -h $(HOST) -p $(PORT)
	./client -c language -h $(HOST) -p $(PORT)
	./client -c country -h $(HOST) -p $(PORT)
	./client -c content_rating -h $(HOST) -p $(PORT)
	./client -c budget -h $(HOST) -p $(PORT)
	./client -c title_year -h $(HOST) -p $(PORT)
	./client -c actor_2_facebook_likes -h $(HOST) -p $(PORT)
	./client -c imdb_score -h $(HOST) -p $(PORT)
	./client -c aspect_ratio -h $(HOST) -p $(PORT)
	./client -c movie_facebook_likes -h $(HOST) -p $(PORT)
	./client -c color -h $(HOST) -p $(PORT)
	./client -c color -h $(HOST) -p $(PORT)
	./client -c color -h $(HOST) -p $(PORT) 
	
clean:
	find /ilab/users/bcs115/Desktop/cs214project3 -type f -name '*-sorted-*' -delete
	find /ilab/users/bcs115/Desktop/cs214project3 -type f -name 'Client*' -delete
