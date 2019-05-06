setwd("D:/Datos")
install.packages("googlesheets", dep=T) #Package required to read from google spreadsheet
install.packages("dplyr", dep=T)
install.packages("curl", dep=T) #Package required to read from google spreadsheet
library(googlesheets)
library(dplyr)
library(curl)
#Load the google sheet onto R
book <- gs_url
("https://docs.google.com/spreadsheets/d/1jTWjASB6MsK5vJMhU0bBoJy8_Vqje_kH4lxWZHC0zV8/edit#gid=0")
data <- gs_read_csv(book, ws=1)
write.csv(data, "practicasucm.csv")

temperatura <- data$Ftemp
fecha <- data$Date
orden <- (1:78)
fs <- 0.4
plot(orden, temperatura)
lines(orden, temperatura)
plot(lowess(orden, temperatura, f=fs), type="l",
     col="blue", lwd=5, ylim=c(0,30), xaxt="n",
     xlab="", ylab="º C", main="Evolución temperatura")
axis(side=1, at=orden[seq(1, 78, by=5)], labels=paste(fecha)[seq(1, 78, by=5)], las=2, cex.axis=0.8)
