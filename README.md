# Vehicle Data Management

Write a program in C to manage information of Cars and its owners using array of structures. There are two structures in a program named as Vehicle and Owner.
An array with the IDs of this car's owners is owners_ID. An owner can have a maximum of 5 cars.

1. Write a function to add a new owner (making sure they don't exist already).
2. Write a function to add a new car to the owner. (if the owner already has 5 vehicles then don’t allow new purchase)
3. Delete a car by ID (also delete car’s entry from owner of this car and if the owner doesn't have another car then delete that owner’s entry too)
4. Write a function to list all the cars of particular owner in ascending order of year of manufacture.
5. Delete all cars from the structure above that have a manufacturing year before 1990. (Also delete car’s entry from owner of this car and if the owner doesn't have another car then delete that owner’s entry too)
6. Write a function to find out owner with maximum and second maximum number of vehicles. (multiple entries should be retrieved).
7. Find out the owners who purchased more than 1, 2-wheeler vehicles in the same year.
8. Write a function to find out the price of the costliest vehicle owned by the owner entered by the user. (User can enter the name of the owner or Owner ID)
9. Find the owners who own more than one vehicle of the brand chosen by the user.
10. List the owners who purchased 3-wheeler in the year provided by the user.
