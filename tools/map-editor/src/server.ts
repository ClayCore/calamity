import app from './app';

const server = app.listen(app.get('port'), () => {
    console.log('   APp is running at http://localhost:%d', app.get('port'));
});

export default server;
