{
  x = scan("~/Desktop/x.csv", sep=",")
g = x[x<1]
t = scan("~/Desktop/t.csv", sep=",")
y = scan("~/Desktop/y.csv", sep=",")
fun = tibble(t=t, y=y)
p = ggplot(data=tibble(g=g), aes(x = g)) + 
  geom_histogram(aes(y = ..density..), bins = 1000) +
  geom_line(data=fun, aes(x=t, y=y, color="red"))

print(p)
}

