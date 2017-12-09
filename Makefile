make default:
	gcc -g -Wall -pthread -lm client.c -o client
	gcc -g -Wall -pthread -lm server.c -o server
	
client:
	gcc -g -pthread -lm client.c -o client
	
server:
	gcc -g -pthread -lm server.c -o servers

test:
	./client -c color -h less.cs.rutgers.edu -p 9000
	./client -c director_name -h less.cs.rutgers.edu -p 9000
	./client -c num_critic_for_reviews -h less.cs.rutgers.edu -p 9000
	./client -c duration -h less.cs.rutgers.edu -p 9000
	./client -c director_facebook_likes -h less.cs.rutgers.edu -p 9000
	./client -c actor_3_facebook_likes -h less.cs.rutgers.edu -p 9000
	./client -c actor_2_name -h less.cs.rutgers.edu -p 9000
	./client -c actor_1_facebook_likes -h less.cs.rutgers.edu -p 9000
	./client -c movie_title -h less.cs.rutgers.edu -p 9000
	./client -c num_voted_users -h less.cs.rutgers.edu -p 9000
	./client -c cast_total_facebook_likes -h less.cs.rutgers.edu -p 9000
	./client -c actor_3_name -h less.cs.rutgers.edu -p 9000
	./client -c facenumber_in_poster -h less.cs.rutgers.edu -p 9000
	./client -c plot_keywords -h less.cs.rutgers.edu -p 9000
	./client -c movie_imdb_link -h less.cs.rutgers.edu -p 9000
	./client -c num_user_for_reviews -h less.cs.rutgers.edu -p 9000
	./client -c language -h less.cs.rutgers.edu -p 9000
	./client -c country -h less.cs.rutgers.edu -p 9000
	./client -c content_rating -h less.cs.rutgers.edu -p 9000
	./client -c budget -h less.cs.rutgers.edu -p 9000
	./client -c title_year -h less.cs.rutgers.edu -p 9000
	./client -c actor_2_facebook_likes -h less.cs.rutgers.edu -p 9000
	./client -c imdb_score -h less.cs.rutgers.edu -p 9000
	./client -c aspect_ratio -h less.cs.rutgers.edu -p 9000
	./client -c movie_facebook_likes -h less.cs.rutgers.edu -p 9000
	./client -c color -h less.cs.rutgers.edu -p 9000
	./client -c color -h less.cs.rutgers.edu -p 9000
	./client -c color -h less.cs.rutgers.edu -p 9000 
	
clean:
	find /ilab/users/bcs115/Desktop/cs214project3 -type f -name '*-sorted-*' -delete
	find /ilab/users/bcs115/Desktop/cs214project3 -type f -name 'Client*' -delete
