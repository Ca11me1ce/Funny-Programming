;p1
(define (PAIR a b) (lambda (p) (p a b)))
(define (LEFT pair) (pair (lambda (a b) a)))
(define (RIGHT pair) (pair (lambda (a b) b)))

;p2 (Assuming n be non-negative integer)
(define (funPower f n)
   (if (<= n 0)
       (lambda (x) x)
       (lambda (x) ((funPower f (- n 1)) (f x)))))

;p3 (lst can be anything, return 0 if lst is not a list)
(define (depthOfList lst)
   (cond
      ((null? lst) 1)
      ((list? lst) 
         (max (+ 1 (depthOfList (car lst)))
				  (depthOfList (cdr lst))))
      (else 0)))

;p4 (Assuming n be a nonnegtive integer, b be any number)
(define (exptFast b n)
   (cond
      ((= n 0) 1)
      ((= n 1) b)
      ((even? n) ((lambda (x) (* x x)) (exptFast b (/ n 2))))
      (else (* b ((lambda (x) (* x x)) (exptFast b (/ (- n 1) 2)))))))

;p5 
;a) (Assuming lst contains only #t or #f)
(define (allTrue lst)
  (fold-left (lambda (ans e) (and ans e)) #t lst))

;b) (Assuming lst is a list contains only numbers, only lists, or only strings)
;   (return empty list if lst is empty list (will not be tested on) )
(define (sum lst)
   (cond
      ((null? lst) '())
      ((number? (car lst)) (fold-left + 0 lst))
      ((list? (car lst)) (fold-left append '() lst))
      ((string? (car lst)) (fold-left string-append "" lst))))

;c) (Assuming lst contains a list of lists with equal length)
;   (map on lists with different lengths is undefined in some versions of interpreters)

; no use of apply
(define (zip lst)
   (fold-left (lambda (a b) (map append a b))
              (map list (car lst))
              (map (lambda (a) (map list a)) (cdr lst))))

; using cons instead of append and list
(define (zipp lst)
   (fold-right (lambda (a b) (map cons a b))
               (map (lambda (a) '()) (car lst))
               lst))

; using apply 
;(this may not work in some versions of interpreters (where apply only take one func and one list) )
(define (zippp lst)
   (apply map list lst))
