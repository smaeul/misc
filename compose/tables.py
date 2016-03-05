#
# tables.py
# Based in part on a work by Christopher Olah <chris@colah.ca>
# I believe this file is too trivial to be copyrightable, and is therefore public domain.
# vim: expandtab:sts=2:sw=2:ts=8:tw=110
#

arrows = [
  ('←', '←←'),
  ('↑', '↑↑'),
  ('→', '→→'),
  ('↓', '↓↓'),
  ('↔', '←→'),
  ('↔', '→←'),
  ('↕', '↑↓'),
  ('↕', '↓↑'),
  ('↖', '←↑'),
  ('↖', '↑←'),
  ('↗', '→↑'),
  ('↗', '↑→'),
  ('↘', '→↓'),
  ('↘', '↓→'),
  ('↙', '←↓'),
  ('↙', '↓←'),
  ('⇐', '=←'),
  ('⇑', '=↑'),
  ('⇒', '=→'),
  ('⇓', '=↓'),
]

bullets = [
  ('•', 'b1'),
  ('‣', 'b2'),
  ('◆', 'b3'),
  ('◇', 'B3'),
  ('■', 'b5'),
  ('□', 'B5'),
  ('▪', 'b5'),
  ('▫', 'B5'),
]

cards = [
  ('♠', 'spade'),
  ('♡', 'heart'),
  ('♢', 'diamd'),
  ('♣', 'clubs'),
]

greek = [
  ('α', 'alpha'),
  ('β', 'beta'),
  ('γ', 'gamma'),
  ('δ', 'delta'),
  ('ε', 'epsilon'),
  ('ζ', 'zeta'),
  ('η', 'eta'),
  ('θ', 'theta'),
  ('ι', 'iota'),
  ('κ', 'kappa'),
  ('λ', 'lambda'),
  ('μ', 'mu'),
  ('ν', 'nu'),
  ('ξ', 'xi'),
  ('ο', 'omicron'),
  ('π', 'pi'),
  ('ρ', 'rho'),
  ('σ', 'sigma'),
  ('τ', 'tau'),
  ('υ', 'upsilon'),
  ('φ', 'phi'),
  ('χ', 'chi'),
  ('ψ', 'psi'),
  ('ω', 'omega'),
  ('Α', 'Alpha'),
  ('Β', 'Beta'),
  ('Γ', 'Gamma'),
  ('Δ', 'Delta'),
  ('Ε', 'Epsilon'),
  ('Ζ', 'Zeta'),
  ('Η', 'Eta'),
  ('Θ', 'Theta'),
  ('Ι', 'Iota'),
  ('Κ', 'Kappa'),
  ('Λ', 'Lambda'),
  ('Μ', 'Mu'),
  ('Ν', 'Nu'),
  ('Ξ', 'Xi'),
  ('Ο', 'Omicron'),
  ('Π', 'Pi'),
  ('Ρ', 'Rho'),
  ('Σ', 'Sigma'),
  ('Τ', 'Tau'),
  ('Υ', 'Upsilon'),
  ('Φ', 'Phi'),
  ('Χ', 'Chi'),
  ('Ψ', 'Psi'),
  ('Ω', 'Omega'),
]

music = [
  ('♭', 'b-'),
  ('♮', 'n0'),
  ('♯', 's+'),
]

operators = [
  ('≠', '=/'),
  ('≠', '/='),
  ('≈', '~~'),
  ('≉', '~/'),
  ('≅', '=~'),
  ('≟', '=?'),
  ('≡', '=_'),
  ('≥', '>='),
  ('≫', '>>'),
  ('≤', '<='),
  ('≪', '<<'),
  ('⋄', '<>'),
  ('±', '+-'),
  ('∓', '-+'),
  ('√', 'v/'),
  ('√', 'sqrt'),
  ('⋅', '.-'),
  ('⋅', '.0'),
  ('⋅', 'cdot'),
  ('×', 'xx'),
  ('÷', '-:'),
  ('÷', ':-'),
  ('¬', '-,'),
  ('¬', 'not'),
  ('⊕', '+0'),
  ('⊕', '+O'),
  ('⊕', '+o'),
  ('⊕', '0+'),
  ('⊕', 'O+'),
  ('⊕', 'o+'),
  ('∂', 'df'),
  ('∇', 'grad'),
  ('∫', 'int'),
  ('∬', 'iint'),
  ('∭', 'iiint'),
  ('∈', 'in'),
  ('∉', 'nin'),
  ('∋', 'ni'),
  ('⋂', 'isect'),
  ('⋃', 'union'),
  ('∅', '0/'),
  ('∅', 'O/'),
]

punctuation = [
  ('–', '---'),
  ('†', '|-'),
  ('‡', '|='),
  ('…', '..'),
  ('¡', '!!'),
  ('¿', '??'),
  ('‽', '!?'),
  ('⸘', '?!'),
]

symbols = [
  ('Å', 'ang'),
  ('¢', 'c|'),
  ('©', 'co'),
  ('ℎ', 'h/'),
  ('ℏ', 'h-'),
  ('Ω', 'ohm'),
  ('℗', 'op'),
  ('℗', 'po'),
  ('®', 'or'),
  ('®', 'ro'),
  ('℞', 'Rx'),
  ('℠', 'sm'),
  ('™', 'tm'),
  ('°', '0*'),
  ('°', '*0'),
  ('∞', '88'),
  ('¤', '$$'),
  ('§', 'SO'),
  ('§', 'So'),
]

# I believe these are the fake superscripts...
superscripts = [
  ('ʰ', '^h'),
  ('ⁱ', '^i'),
  ('ʲ', '^j'),
  ('ⁿ', '^n'),
  ('ᵒ', '^o'),
  ('ᵖ', '^p'),
  ('ʳ', '^r'),
  ('ᵗ', '^t'),
  ('ᵘ', '^u'),
  ('ᵛ', '^v'),
  ('ʷ', '^w'),
  ('ʸ', '^y'),
]