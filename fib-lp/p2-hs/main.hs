data Ident = String
data Command a  = Assign Ident a
                |  Print Ident
