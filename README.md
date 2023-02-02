# Project_c-part2

Project of C


  _ _ _ _ _ _ _ _                             _ _ _ _ _ _ _                            _ _ _ _ _ _ _ _ 
|                 |                          |             |                          |                |
|                 |                          |             |                          |                |
|  Five_client.c  |                          |   query.c   |_ _ _ _ _ _ _ _ _ _ _ _ _ |      db.c      |
|                 |                          |             |                          |                |
|_ _ _ _ _ _ _ _ _\                          |_ _ _ _ _ _ _|                          |_ _ _ _ _ _ _ _ |     
                   \                         /             \                         /
                    \                       /               \                       /
                     \                     /                  \                    /
                      \_ _ _ _ _ _ _ _ _  /                    \ _ _ _ _ _ _ _ _ _/
                       |                  |                     |                 |
                       |                  | _ _ _ _ _ _ _ _ _ _ |                 |
                       |  thread_server.c |                     |    validate.c   |
                       |                  |                     |                 |
                       |_ _ _ _ _ _ _ _ _ |                     |_ _ _ _ _ _ _ _ _|
                                           \
                                            \
                                             \_ _ _ _ _ _ _ _ _ 
                                             |                  |
                                             |                  |
                                             |    file.c        |
                                             |                  |
                                             |_ _ _ _ _ _ _ _ _ |






to run the the application
1. make server
2. make client
3. ./server port_number file.csv
3. ./client port_number

the application init.c read the lines on file .csv and send to the validate.c file.
The validate.c check for date mistake ,the rigth format for date is yyyy/mmm/dd, check the size of id of 9 digist and the phone number of 10 digits.
If there is any problem he reject the insertion and send a message error with the field containing the mistake. 
After the file been check , he send the data to db , where he save the in the array of struct. 
After he save the application, it open the console to make a select an set , the right format to do the select is:
select field = value

the right format to do the set is:
set firstname=name lastname=name birth=yyyy/mm/dd idnumber=123456789 phonenumber=0123456789 debt=value debtdate=yyyy/mm/dd
