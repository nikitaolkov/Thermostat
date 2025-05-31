const char main_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="ru">
<head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta charset="UTF-8">
    <title>Холодильник</title>

    <style>

    body
{
    font-family: fantasy;
    background-color: #EAE7DC;
    color: black;
    letter-spacing: 0.75px;
    /*-webkit-text-stroke: 0.75px black;*/
}

h1 
{
    text-align: center;
}

header 
{
    display: flex;
}

header p 
{
    border: 2px solid #8E8D8A;
    align-content: center;
    margin: 10px 0px;
    padding: 10px;
}

nav 
{
    border: 2px solid #8E8D8A;
    padding: 10px;
    margin: 10px 20px;
}

nav ul 
{
    list-style-type: none;
    align-content: center;
    /*border: 1px solid #66FCF1;*/
    display: flex;
    margin: 0px;
    padding: 5px;
}

nav ul li 
{
    display: inline-block;
    border: 2px solid #8E8D8A;
    background-color: #EAE7DC;
    margin: 5px;
    padding: 5px 10px;
}

nav ul li a
{
    text-decoration: none;
    margin: 0px;
    padding: 0px;
    /*color: #37ad7c;*/
    color: black;
    /*-webkit-text-stroke: 0.75px black;*/
}

nav ul li a:hover
{
    color: #E85A4F;
}

nav ul li a.active
{
    color: #f59042;
}

nav ul li a.active:hover
{
    color: #E85A4F;
}

.main-section 
{
    display: flex;
}

footer 
{
    text-align: center;
}

hr 
{
    border: none;
    color: #8E8D8A;
    background-color: #8E8D8A;
    height: 2px;
}

header .vl 
{
    border-left: 2px solid #8E8D8A;
    height: auto;
}

button 
{
    font-family: fantasy;
    border: 2px solid black;
    padding: 3px 4px;
    margin-top: 2px;
    color: black;
    letter-spacing: 0.75px;
    /*-webkit-text-stroke: 0.75px black;*/
}

button:hover 
{
  color: #E85A4F;
}

@media (max-width:768px) 
{
    header 
    {
        display: block;
        margin: 0 auto;
    }
    
    nav 
    {
        border: 2px solid #8E8D8A;
        align-content: center;
        padding: 0px;
        margin: 0px 0px;
    }

    nav ul 
    {
        list-style-type: none;
        align-content: center;
        /*border: 1px solid #66FCF1;*/
        display: flex;
        margin: 0px;
        padding: 0px;
    }

    nav ul li 
    {
        display: inline-block;
        border: 2px solid #8E8D8A;
        background-color: #EAE7DC;
        margin: 5px;
        padding: 5px 3px;
    }
}

</style>
    
</head>
<body>
    <header>
       <p>Термостат ( v. 0.01 )</p>
       <nav>
          <ul>
            <li><a class = "active" href="/main.html">Главная</a></li>
            <li><a href="/options.html">Опции</a></li>
            <li><a href="/news.html">Новости</a></li>
            <li><a href="/contacts.html">Контакты</a></li>
          </ul>
        </nav>
    </header>
        <hr>
        <h1>Управление температурой</h1>
        <hr>
        <section class = "main-section">
          <fieldset>
            <legend>Показания датчика DHT22</legend>
            <p>
                ТЕМПЕРАТУРА: <span id = "temperature_fridge">%TEMP_1%</span> &deg;C<br>
                ВЛАЖНОСТЬ: <span id = "temperature_freezer">%TEMP_2%</span> %<br>
            </p>
          </fieldset>

          <fieldset>
            <legend>Управление реле</legend>
            <button onclick="relaySwitch(event)" id="relay_button">Включить</button>
          </fieldset>
        </section>
    <footer>
        <hr>
        <p>Все права защищены.</p>
    </footer>
    
</body>
    <script>
        setInterval(function () {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    var temperature_str = this.responseText;
                    var temperature_values = temperature_str.split('/');
                  
                    document.getElementById("temperature_fridge").innerHTML = temperature_values[0];
                    document.getElementById("temperature_freezer").innerHTML = temperature_values[1];
                }
            };
            xhttp.open("GET", "/temperature", true);
            xhttp.send();
        }, 5000);

        function relaySwitch(event) {
          event.target.style.color = 'black';
          var xhttp = new XMLHttpRequest();
          xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
              var button_new_text = this.responseText;
              
              document.getElementById("relay_button").innerHTML = button_new_text;
            }
          };
          xhttp.open("GET", "/relay_switch", true);
          xhttp.send();
        }

    </script>
</html>
)rawliteral";

const char options_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="ru">
<head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta charset="UTF-8">
    <link href="main.css" rel="stylesheet" type="text/css" />
    <link rel="icon" href="main_icon.png">
    <title>Холодильник</title>

     <style>
body
{
    font-family: fantasy;
    background-color: #EAE7DC;
    color: black;
    letter-spacing: 0.75px;
    /*-webkit-text-stroke: 0.75px black;*/
}

h1 
{
    text-align: center;
}

header 
{
    display: flex;
}

header p 
{
    border: 2px solid #8E8D8A;
    align-content: center;
    margin: 10px 0px;
    padding: 10px;
}

nav 
{
    border: 2px solid #8E8D8A;
    padding: 10px;
    margin: 10px 20px;
}

nav ul 
{
    list-style-type: none;
    align-content: center;
    /*border: 1px solid #66FCF1;*/
    display: flex;
    margin: 0px;
    padding: 5px;
}

nav ul li 
{
    display: inline-block;
    border: 2px solid #8E8D8A;
    background-color: #EAE7DC;
    margin: 5px;
    padding: 5px 10px;
}

nav ul li a
{
    text-decoration: none;
    margin: 0px;
    padding: 0px;
    color: black;
    /*-webkit-text-stroke: 0.75px black;*/
}

nav ul li a:hover
{
    color: #E85A4F;
}

nav ul li a.active
{
    color: #f59042;
}

nav ul li a.active:hover
{
    color: #E85A4F;
}

.main-section 
{
    display: flex;
}

footer 
{
    text-align: center;
}

hr 
{
    border: none;
    color: #8E8D8A;
    background-color: #8E8D8A;
    height: 2px;
}

header .vl 
{
    border-left: 2px solid #8E8D8A;
    height: auto;
}

button 
{
    font-family: fantasy;
    border: 2px solid black;
    padding: 3px 4px;
    margin-top: 2px;
    color: black;
    letter-spacing: 0.75px;
    /*-webkit-text-stroke: 0.75px black;*/
}

button:hover 
{
  color: #E85A4F;
}

input 
{
  font-family: fantasy;
  color: black;
  letter-spacing: 0.75px;
  margin-top: 3px;
  margin-left 3px;
  height: 100%;
  width: 100%;
}

label
{
  font-family: fantasy;
  color: black;
  letter-spacing: 0.75px;
  margin-top: 3px;
  margin-left 3px;
}

@media (max-width:768px) 
{
    header 
    {
        display: block;
        margin: 0 auto;
    }
    
    nav 
    {
        border: 2px solid #8E8D8A;
        align-content: center;
        padding: 0px;
        margin: 0px 0px;
    }

    nav ul 
    {
        list-style-type: none;
        align-content: center;
        /*border: 1px solid #66FCF1;*/
        display: flex;
        margin: 0px;
        padding: 0px;
    }

    nav ul li 
    {
        display: inline-block;
        border: 2px solid #8E8D8A;
        background-color: #EAE7DC;
        margin: 5px;
        padding: 5px 3px;
    }
}

</style>
    
</head>
<body>
    <header>
       <p>Термостат ( v. 0.01 )</p>
       <nav>
          <ul>
            <li><a href="/main.html">Главная</a></li>
            <li><a class = "active" href="/options.html">Опции</a></li>
            <li><a href="/news.html">Новости</a></li>
            <li><a href="/contacts.html">Контакты</a></li>
          </ul>
        </nav>
    </header>
    
    <main>
        <section>
            <hr>
            <h1>Опции веб-интерфейса</h1>
            <hr>
            <form action="/get_new_option_value">
              <fieldset>
                <legend>Температура</legend>
                  <label for="min_temp_input">Минимальная температура (в градусах Цельсия)</label>
                  <input type="number" id="min_temp_input" name="min_temp" maxlength="3">
              </fieldset>

              <fieldset>
                <legend>Параметры подключения</legend>
                  <fieldset>
                    <legend>Точка доступа</legend>
                      <label for="ssid_input">Имя</label>
                      <input type="text" id="ssid_input" name="ssid" maxlength="10">

                      <label for="pass_input">Пароль</label>
                      <input type="text" id="pass_input" name="pass" minlength="8" maxlength="15">
                  </fieldset>
              </fieldset>

                <button type="submit">Сохранить</button>
            </form>
        </section>
    </main>
    
    <footer>
        <hr>
        <p>Все права защищены.</p>
    </footer>
    
</body>

<script>
    document.addEventListener("DOMContentLoaded", function() 
    {
      (function() 
      {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
          var parameters_str = this.responseText;
          var parameters_list = parameters_str.split('/');

          document.getElementById("min_temp_input").value = parameters_list[0];
          document.getElementById("ssid_input").value = parameters_list[1];
          document.getElementById("pass_input").value = parameters_list[2];
        }
      };
      xhttp.open("GET", "/get_options", true);
      xhttp.send();
   })();
    });
  </script>

</html>
)rawliteral";

const char news_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="ru">
<head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta charset="UTF-8">
    <link href="main.css" rel="stylesheet" type="text/css" />
    <link rel="icon" href="main_icon.png">
    <title>Холодильник</title>
    <style>
        main section ul li p 
        {
           text-indent: 20px;
        }
body
{
    font-family: fantasy;
    background-color: #EAE7DC;
    color: black;
    letter-spacing: 0.75px;
    /*-webkit-text-stroke: 0.75px black;*/
}

h1 
{
    text-align: center;
}

header 
{
    display: flex;
}

header p 
{
    border: 2px solid #8E8D8A;
    align-content: center;
    margin: 10px 0px;
    padding: 10px;
}

nav 
{
    border: 2px solid #8E8D8A;
    padding: 10px;
    margin: 10px 20px;
}

nav ul 
{
    list-style-type: none;
    align-content: center;
    /*border: 1px solid #66FCF1;*/
    display: flex;
    margin: 0px;
    padding: 5px;
}

nav ul li 
{
    display: inline-block;
    border: 2px solid #8E8D8A;
    background-color: #EAE7DC;
    margin: 5px;
    padding: 5px 10px;
}

nav ul li a
{
    text-decoration: none;
    margin: 0px;
    padding: 0px;
    color: black;
    /*-webkit-text-stroke: 0.75px black;*/
}

nav ul li a:hover
{
    color: #E85A4F;
}

nav ul li a.active
{
    color: #f59042;
}

nav ul li a.active:hover
{
    color: #E85A4F;
}

.main-section 
{
    display: flex;
}

footer 
{
    text-align: center;
}

hr 
{
    border: none;
    color: #8E8D8A;
    background-color: #8E8D8A;
    height: 2px;
}

header .vl 
{
    border-left: 2px solid #8E8D8A;
    height: auto;
}

@media (max-width:768px) 
{
    header 
    {
        display: block;
        margin: 0 auto;
    }
    
    nav 
    {
        border: 2px solid #8E8D8A;
        align-content: center;
        padding: 0px;
        margin: 0px 0px;
    }

    nav ul 
    {
        list-style-type: none;
        align-content: center;
        /*border: 1px solid #66FCF1;*/
        display: flex;
        margin: 0px;
        padding: 0px;
    }

    nav ul li 
    {
        display: inline-block;
        border: 2px solid #8E8D8A;
        background-color: #EAE7DC;
        margin: 5px;
        padding: 5px 3px;
    }
}

</style>
</head>
<body>
    <header>
       <p>Термостат ( v. 0.01 )</p>
       <nav>
          <ul>
            <li><a href="/main.html">Главная</a></li>
            <li><a href="/options.html">Опции</a></li>
            <li><a class = "active" href="/news.html">Новости</a></li>
            <li><a href="/contacts.html">Контакты</a></li>
          </ul>
        </nav>
    </header>
    
    <main>
        <section>
            <hr>
            <h1>Новости</h1>
            <hr>
            <ul>
                <p><u>27.08.24</u>:</p>
                <li>
                  <p>Добавлена группа настроек: "Параметры сети".</p>
                </li>
                <p><u>24.08.24</u>:</p>
                <li>
                    <p>В данной версии внесены следующие изменения:</p>
                    <ul>
                      <li><p>Изменена цветовая гамма веб-интерфейса.</p></li>
                      <li><p>Изменено меню настроек.</p></li>
                    </ul>
                </li>
                <p><u>10.08.24</u>:</p>
                <li>
                    <p>Веб-интерфейс был адаптирован под мобильные устройства.</p>
                </li>
                <p><u>09.08.24</u>:</p>
                <li>
                    <p>Версия 0.01 веб-интерфейса была реализована на ESP8266.</p>
                </li>
               <p><u>07.08.24</u>:</p>
                <li>
                    <p>Была создана версия 0.01.</p>
                </li>
            </ul>
        </section>
    </main>
    
    <footer>
        <hr>
        <p>Все права защищены.</p>
    </footer>
    
</body>
</html>
)rawliteral";

const char contacts_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="ru">
<head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta charset="UTF-8">
    <link href="main.css" rel="stylesheet" type="text/css" />
    <link rel="icon" href="main_icon.png">
    <title>Холодильник</title>
<style>
main section ul li p 
{
  text-indent: 20px;
}

body
{
    font-family: fantasy;
    background-color: #EAE7DC;
    color: black;
    letter-spacing: 0.75px;
    /*-webkit-text-stroke: 0.75px black;*/
}

h1 
{
    text-align: center;
}

header 
{
    display: flex;
}

header p 
{
    border: 2px solid #8E8D8A;
    align-content: center;
    margin: 10px 0px;
    padding: 10px;
}

nav 
{
    border: 2px solid #8E8D8A;
    padding: 10px;
    margin: 10px 20px;
}

nav ul 
{
    list-style-type: none;
    align-content: center;
    /*border: 1px solid #66FCF1;*/
    display: flex;
    margin: 0px;
    padding: 5px;
}

nav ul li 
{
    display: inline-block;
    border: 2px solid #8E8D8A;
    background-color: #EAE7DC;
    margin: 5px;
    padding: 5px 10px;
}

nav ul li a
{
    text-decoration: none;
    margin: 0px;
    padding: 0px;
    color: black;
    /*-webkit-text-stroke: 0.75px black;*/
}

nav ul li a:hover
{
    color: #E85A4F;
}

nav ul li a.active
{
    color: #f59042;
}

nav ul li a.active:hover
{
    color: #E85A4F;
}

.main-section 
{
    display: flex;
}

footer 
{
    text-align: center;
}

hr 
{
    border: none;
    color: #8E8D8A;
    background-color: #8E8D8A;
    height: 2px;
}

header .vl 
{
    border-left: 2px solid #8E8D8A;
    height: auto;
}

@media (max-width:768px) 
{
    header 
    {
        display: block;
        margin: 0 auto;
    }
    
    nav 
    {
        border: 2px solid #8E8D8A;
        align-content: center;
        padding: 0px;
        margin: 0px 0px;
    }

    nav ul 
    {
        list-style-type: none;
        align-content: center;
        /*border: 1px solid #66FCF1;*/
        display: flex;
        margin: 0px;
        padding: 0px;
    }

    nav ul li 
    {
        display: inline-block;
        border: 2px solid #8E8D8A;
        background-color: #EAE7DC;
        margin: 5px;
        padding: 5px 3px;
    }
}

</style>
</head>
<body>
    <header>
       <p>Термостат ( v. 0.01 )</p>
       <nav>
          <ul>
            <li><a href="/main.html">Главная</a></li>
            <li><a href="/options.html">Опции</a></li>
            <li><a href="/news.html">Новости</a></li>
            <li><a class = "active" href="/contacts.html">Контакты</a></li>
          </ul>
        </nav>
    </header>
    
    <main>
        <section>
            <hr>
            <h1>Контактная информация</h1>
            <hr>
            <p>
               Автор: Ольков Никита, ИТ-0940323 <br>
               Реализовано в рамках дисциплины "Технологии разработки WEB-приложений"
            </p>
        </section>
    </main>
    
    <footer>
        <hr>
        <p>Все права защищены.</p>
    </footer>
    
</body>
</html>
)rawliteral";
