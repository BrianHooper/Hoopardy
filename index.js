const categories = 
[
    "CAT-01", 
    "CAT-02", 
    "CAT-03", 
    "CAT-04", 
]; 

const questions = 
[
    "WHAT ITEM DID THE HOOPERS PURCHASE INSTEAD OF TAKING BRIAN AND KELSI TO DISNEYLAND?", 
    "WHAT IS THIS WOMANS NAME?", 
    "WHAT WAS KELSIS FIRST CAR?", 
    "WHAT ITEM DID ANDY USE TO CATCH TEENAGE BRIAN SNEAKING OUT?", 
    "KELSIS FIRST TATTOO WAS A PAINTING BY WHICH ARTIST?", 
    "WHAT IS THE NAME OF THE TOWN WHERE ANDY AND NINA LIVE?",
    "WHAT WAS UNCLE ERNIES JOB?",
    "08",
    "09",
    "10",
    "11",
    "12",
    "13",
    "14",
    "15",
    "16",
]; 

function showz(card) {
    var t = card.querySelector(".button-points-text");
    t.classList.toggle("button-points-faded");

    t.classList.add("button-price-text-hidden");
    t.classList.remove("button-price-text-visible");
    var s = card.parentNode.querySelector(".question-card");
    s.classList = ["question-card question-card-visible"];
}

function hide(card) {
    card.classList.remove('question-card-visible');
    card.classList.add('question-card-hidden');
}


// function showQuestion(card) {
    
//     var question = card.dataset.question;
//     card.innerText = card.dataset.prizeAmount;
//     var page = document.querySelector("#page");

//     var overlay = document.createElement("div");
//     overlay.id = "clue-overlay";
//     var box = document.createElement("div");
//     box.id = "clue-card"

//     var textbox = document.createElement("div");
//     textbox.classList.add("box-text");
//     textbox.innerText = question;
//     box.appendChild(textbox);

//     overlay.appendChild(box);
//     overlay.addEventListener("click", close);
//     page.appendChild(overlay);
// };

// window.addEventListener("load", (event) => {
//     var t = document.getElementsByClassName("price-box");
//     for (var i = 0; i < t.length; i++) {
//         var prizeAmount = (200 * (Math.floor(i / 4) + 1)).toString();
//         t[i].dataset.prizeAmount = prizeAmount;
//         t[i].dataset.question = questions[i];
//     }

//     var cats = document.getElementsByClassName("category");
//     for (var i = 0; i < cats.length; i++) {
//         cats[i].innerText = categories[i];
//     }
// });