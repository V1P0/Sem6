/*jslint browser:true  */
/*jslint devel: true */
/*global
  alert, confirm, console, prompt,Image
*/
// definicja list słów dla poszczególnych kategorii
const categories = {
  animals: ["LION", "ELEPHANT", "GIRAFFE", "RHINOCEROS", "HIPPOPOTAMUS"],
  fruits: ["APPLE", "BANANA", "ORANGE", "PEAR", "PINEAPPLE"],
  countries: ["POLAND", "JAPAN", "BRAZIL", "AUSTRALIA", "EGYPT"],
};

const alphabetContainer = document.querySelector(".alphabet-container");
const categoriesContainer = document.querySelector(".categories");
const gameContainer = document.querySelector(".game-container");
const resetButton = document.querySelector("#reset-button");
const changeCategoryButton = document.querySelector("#change-button");
const saveButton = document.querySelector("#save-button");
const wordContainer = document.querySelector(".word-container");

let theWord = "";
let guessNumber = 0;
let theCategory = "";
let correctLetters = 0;

changeCategoryButton.addEventListener("click", () => {
  categoriesContainer.classList.remove("display-none");
  gameContainer.classList.add("display-none");
  theWord = "";
  guessNumber = 0;
});

resetButton.addEventListener("click", resetGame);

categoriesContainer.addEventListener("click", (event) => {
  const category = event.target.dataset.category;
  if (category) {
    categoriesContainer.classList.add("display-none");
    gameContainer.classList.remove("display-none");

    // uzyskanie losowego słowa dla danej kategorii
    theCategory = category;
    const word = getRandomWord(category);

    // wywołanie funkcji ustawiającej słowo i rysującej szubienicę
    setWord(word);
  }
});

alphabetContainer.addEventListener("click", handleLetterClick);
saveButton.addEventListener("click", saveGameState);

document.addEventListener("DOMContentLoaded", function () {
  const gameState = JSON.parse(localStorage.getItem("hangmanGameState"));
  const wordContainer = document.querySelector(".word-container");
  const water = document.querySelector(".water");

  if (gameState) {
    theWord = gameState.theWord;
    guessNumber = gameState.guessNumber;
    theCategory = gameState.theCategory;
    if (theCategory) {
      categoriesContainer.classList.add("display-none");
      gameContainer.classList.remove("display-none");
    }
    correctLetters = gameState.correctLetters;
    setWord(theWord);

    water.style.height = guessNumber * 10 + "%";
    water.style.backgroundColor = "blue";
    water.style.transition = "all 0.5s";
    water.style.transitionTimingFunction = "ease-in-out";

    alphabetContainer.querySelectorAll("input").forEach((button) => {
      if (gameState.disabledButtons.includes(button.value)) {
        button.disabled = true;
        wordContainer.querySelectorAll(".letter").forEach((letter) => {
          if (letter.textContent === button.value) {
            letter.classList.remove("letter-hidden");
          }
        });
      }
    });
  }
});

// funkcja zwracająca losowe słowo z danej kategorii
function getRandomWord(category) {
  const words = categories[category];
  const randomIndex = Math.floor(Math.random() * words.length);
  return words[randomIndex];
}

function setWord(word) {
  // ustawia słowo do odgadnięcia w elemencie o klasie "word-container"
  wordContainer.innerHTML = "";
  for (let i = 0; i < word.length; i++) {
    const letterContainer = document.createElement("div");
    letterContainer.classList.add("letter-container");
    const letter = document.createElement("div");
    letter.classList.add("letter");
    letter.classList.add("letter-hidden");
    letter.textContent = word[i];
    letterContainer.appendChild(letter);
    wordContainer.appendChild(letterContainer);
  }
  theWord = word;
  console.log(word);
}

function drawHangman(step) {
  const water = document.querySelector(".water");
  guessNumber++;

  if (guessNumber >= 10) {
    water.style.height = guessNumber * 10 + "%";
    water.style.backgroundColor = "blue";
    water.style.transition = "all 0.5s";
    water.style.transitionTimingFunction = "ease-in-out";

    setTimeout(() => {
      alert("Przegrałeś");
      resetGame();
    }, 500);
  } else {
    water.style.height = guessNumber * 10 + "%";
    water.style.backgroundColor = "blue";
    water.style.transition = "all 0.5s";
    water.style.transitionTimingFunction = "ease-in-out";
  }
}

function handleLetterClick(event) {
  const letter = event.target.value;
  if (letter) {
    checkLetter(letter);
  }
  event.target.disabled = true;
}

function checkLetter(event) {
  const letter = event;
  console.log(theWord, letter);

  if (theWord.includes(letter)) {
    const letters = document.querySelectorAll(".letter");
    letters.forEach((element) => {
      if (element.textContent === letter) {
        element.classList.remove("letter-hidden");
        correctLetters++;
      }
    });
    
  } else {
    drawHangman();
  }


  if (correctLetters === theWord.length) {
    setTimeout(() => {
      alert("Wygrałeś");
      resetGame();
    }, 500);
  }
}

function resetGame() {
  // zresetowanie stanu gry
  theWord = "";
  guessNumber = 0;
  correctLetters = 0;
  const water = document.querySelector(".water");
  water.style.height = "0%";
  const letters = document.querySelectorAll(".letter");
  letters.forEach((element) => {
    element.remove();
  });
  alphabetContainer.querySelectorAll("input").forEach((button) => {
    button.disabled = false;
  });
  const newWord = getRandomWord(theCategory);
  setWord(newWord);
  localStorage.removeItem("hangmanGameState");
}

// funkcja do zapisu stanu gry w localStorage
function saveGameState() {
  const disabledButtons = [];
  alphabetContainer.querySelectorAll("input").forEach((button) => {
    if (button.disabled) {
      disabledButtons.push(button.value);
    }
  });

  const gameState = {
    theWord,
    guessNumber,
    theCategory,
    correctLetters,
    disabledButtons,
  };
  localStorage.setItem("hangmanGameState", JSON.stringify(gameState));
}
